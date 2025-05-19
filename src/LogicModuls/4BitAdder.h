#pragma once
#include "LogicCell.h"
#include "LogicGate.h"
#include "DelayCell.h"
#include <format>

class csFullAdder {
public:
	csFullAdder () 
	{ 
		HalfAdd.InvertInp(1);
		NandInp.Inp(0)->addLink(NorInp.Inp(0));
		NandInp.Inp(1)->addLink(NorInp.Inp(1));
		NandInp.OutY().addLink(HalfAdd.Inp(0));
		NorInp.OutY().addLink(HalfAdd.Inp(1));
		HalfAdd.OutY().addLink(CarryAdd.Inp(0));
	}

	void setName(std::string name) {
		NandInp.setName(name + ".NandInp");
		NorInp.setName(name + ".NorInp");
		HalfAdd.setName(name + ".HalfAdd");
		CarryAdd.setName(name + ".CarryAdd");
	}
	void setEventList(csEventList* EventList) {
		NandInp.setEventList(EventList);
		NorInp.setEventList(EventList);
		HalfAdd.setEventList(EventList);
		CarryAdd.setEventList(EventList);
	}

	csLogicInp* A() { return NandInp.Inp(1); }
	csLogicInp* B() { return NandInp.Inp(0); }
	csLogicInp* Cin() { return CarryAdd.Inp(1); }

	csLogicOut& OutNand() { return NandInp.OutY(); }
	csLogicOut& OutNor() { return NorInp.OutY(); }
	csLogicOut& OutSum() { return CarryAdd.OutY(); }
private:
	csNandGate<> NandInp;
	csNorGate<> NorInp;
	csAndGate<> HalfAdd;
	csXorGate<> CarryAdd;
};

template<const int NorWidth>
class csCarryLAhead2 {
public:
	csCarryLAhead2(csEventList* EventList) :
		Driver(EventList),
		And2(EventList),
		NorGate(EventList)
	{ 
		Driver.OutY().addLink(NorGate.Inp(0));
		And2.OutY().addLink(NorGate.Inp(1));
	}
	csLogicInp* Din() { return Driver.Inp(); }
	csLogicInp* And2In(int InpNo) { return And2.Inp(InpNo); }
	csLogicOut& Cout() { return NorGate.OutY(); }
	virtual void setName(std::string name) {
		Driver.setName(name + ".Din");
		And2.setName(name + ".And2");
		NorGate.setName(name + ".NorGate");
	}
protected:
	csDelayCell Driver;
	csAndGate<2> And2;
	csNorGate<NorWidth> NorGate;
};

template<const int NorWidth>
class csCarryLAhead3 : public csCarryLAhead2<NorWidth>
{
public:
	csCarryLAhead3(csEventList* EventList) :
		csCarryLAhead2<NorWidth>(EventList),
		And3(EventList) 
	{
		And3.OutY().addLink(csCarryLAhead2<NorWidth>::NorGate.Inp(2));
	}
	csLogicInp* And3In(int InpNo) { return And3.Inp(InpNo); }
	virtual void setName(std::string name) {
		csCarryLAhead2<NorWidth>::setName(name);
		And3.setName(name + ".And3");
	}
protected:
	csAndGate<3> And3;
};

template<const int NorWidth>
class csCarryLAhead4 : public csCarryLAhead3<NorWidth>
{
public:
	csCarryLAhead4(csEventList* EventList) :
		csCarryLAhead3<NorWidth>(EventList),
		And4(EventList)
	{ 
		And4.OutY().addLink(csCarryLAhead3<NorWidth>::NorGate.Inp(3));
	}
	csLogicInp* And4In(int InpNo) { return And4.Inp(InpNo); }
	virtual void setName(std::string name) {
		csCarryLAhead3<NorWidth>::setName(name);
		And4.setName(name + ".And4");
	}

protected:
	csAndGate<4> And4;
};

template<const int NorWidth>
class csCarryLAhead5 : public csCarryLAhead4<NorWidth>
{
public:
	csCarryLAhead5(csEventList* EventList) :
		csCarryLAhead4<NorWidth>(EventList),
		And5(EventList)
	{
		And5.OutY().addLink(csCarryLAhead4<NorWidth>::NorGate.Inp(4));
	}
	csLogicInp* And5In(int InpNo) { return And5.Inp(InpNo); }
	virtual void setName(std::string name) {
		csCarryLAhead4<NorWidth>::setName(name);
		And5.setName(name + ".And5");
	}

protected:
	csAndGate<5> And5;
};

class cs4BitAdder {
public:
	cs4BitAdder(csEventList* EventList) :
		CarryLAhead2(EventList),
		CarryLAhead3(EventList),
		CarryLAhead4(EventList),
		CarryLAhead5(EventList) 
	{
		CinInvert[0].setEventList(EventList);
		CinInvert[1].setEventList(EventList);
		for (int i = 0; i < 4; ++i) {
			Adder[i].setName(std::format("ADD{}", i));
			Adder[i].setEventList(EventList);
		}
		CarryLAhead2.setName("LAhead2");
		CarryLAhead3.setName("LAhead3");
		CarryLAhead4.setName("LAhead4");
		CarryLAhead5.setName("LAhead5");

		CinInvert[0].OutY().addLinks({ CinInvert[1].Inp(),
										CarryLAhead2.And2In(1),
										CarryLAhead3.And3In(2),
										CarryLAhead4.And4In(3),
										CarryLAhead5.And5In(4), });

		Adder[0].OutNor().addLinks({ CarryLAhead2.Din(),
									 CarryLAhead3.And2In(0),
									 CarryLAhead4.And3In(0),
									 CarryLAhead5.And4In(0) });

		Adder[0].OutNand().addLinks({ CarryLAhead2.And2In(0),
									 CarryLAhead3.And3In(1),
									 CarryLAhead4.And4In(2),
									 CarryLAhead5.And5In(3) });

		Adder[1].OutNor().addLinks({ CarryLAhead3.Din(),
									 CarryLAhead4.And2In(0),
									 CarryLAhead5.And3In(0) });

		Adder[1].OutNand().addLinks({ CarryLAhead3.And3In(0),
									  CarryLAhead3.And2In(1),
									  CarryLAhead4.And4In(1),
									  CarryLAhead4.And3In(2),
									  CarryLAhead5.And5In(2),
									  CarryLAhead5.And4In(3) });

		Adder[2].OutNor().addLinks({ CarryLAhead4.Din(),
									 CarryLAhead5.And2In(0) });

		Adder[2].OutNand().addLinks({ CarryLAhead4.And4In(0),
									  CarryLAhead4.And3In(1),
									  CarryLAhead4.And2In(1),
									  CarryLAhead5.And5In(1),
									  CarryLAhead5.And4In(2),
									  CarryLAhead5.And3In(2) });
	

		Adder[3].OutNor().addLink(CarryLAhead5.Din());
		Adder[3].OutNand().addLinks({ CarryLAhead5.And5In(0),
									  CarryLAhead5.And4In(1),
									  CarryLAhead5.And3In(1),
									  CarryLAhead5.And2In(1)});

		CinInvert[1].OutY().addLink(Adder[0].Cin());
		CarryLAhead2.Cout().addLink(Adder[1].Cin());
		CarryLAhead3.Cout().addLink(Adder[2].Cin());
		CarryLAhead4.Cout().addLink(Adder[3].Cin());
	}

	csLogicInp* Cin() { return CinInvert[0].Inp(); }
	csLogicInp* A(int InpNo) { return Adder[InpNo].A(); }
	csLogicInp* B(int InpNo) { return Adder[InpNo].B(); }

	csLogicOut& Sum(int OutNo) { return Adder[OutNo].OutSum(); }
	void printNet() {
		Cin()->printNet("Cin");
		CinInvert[0].OutY().printNet("INV0");
		CinInvert[1].OutY().printNet("INV1");
		for (int i = 0; i < 4; ++i) {
			A(i)->printNet(std::format("A{}", i));
			B(i)->printNet(std::format("B{}", i));
			Adder[i].OutNor().printNet();
			Adder[i].OutNand().printNet();
		}
	}

private:
	csFullAdder Adder[4];
	csInverter CinInvert[2];
	csCarryLAhead2<2> CarryLAhead2;
	csCarryLAhead3<3> CarryLAhead3;
	csCarryLAhead4<4> CarryLAhead4;
	csCarryLAhead5<5> CarryLAhead5;
};
