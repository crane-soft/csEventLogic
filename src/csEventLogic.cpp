
#include "LogicGate.h"
#include "RippleCnt.h"
#include "FrqDoubler.h"
#include "LogicApp.h"
#include "4BitAdder.h"
class csTestRippleCount : public csLogicApp
{
public:
	csTestRippleCount() :
		RippleCnt(&EventList),
		AndGate(&EventList)
	{
		MainClock.OutY().addLink(RippleCnt.CP());
		RippleCnt.Q(2).addLink(AndGate.Inp(0));
		RippleCnt.Q(3).addLink(AndGate.Inp(1));
		AndGate.OutY().addLink(RippleCnt.MR());
		ProbeAdapter.AddProbes({ &AndGate.OutY(),&RippleCnt.Q(3), &RippleCnt.Q(2),&RippleCnt.Q(1),&RippleCnt.Q(0) });
	}

private:
	csRippleCnt<4> RippleCnt;
	csAndGate<> AndGate;

};


class csTestFrqDouble : public csLogicApp
{
public:
	csTestFrqDouble() :
		FrqDoubler(&EventList, 15)
	{
		MainClock.OutY().addLink(FrqDoubler.CP());
		ProbeAdapter.AddProbes({ &MainClock.OutY(),&FrqDoubler.OutY() });
	}
private:
	csFrqDoubler FrqDoubler;
};

class csTest4BitAdder : public csLogicApp
{
public:
	csTest4BitAdder() :
		m4BitAdder(&EventList),
		TestCnt(&EventList),
		GND(&EventList),
		CntReset(&EventList)
	{
//		m4BitAdder.printNet();

		MainClock.OutY().addLink(TestCnt.CP());
		TestCnt.Q(0).addLink(m4BitAdder.A(0));
		TestCnt.Q(1).addLink(m4BitAdder.A(1));
		TestCnt.Q(2).addLink(m4BitAdder.A(2));
		TestCnt.Q(3).addLink(m4BitAdder.A(3));

		TestCnt.Q(4).addLink(m4BitAdder.B(0));
		TestCnt.Q(5).addLink(m4BitAdder.B(1));
		TestCnt.Q(6).addLink(m4BitAdder.B(2));
		TestCnt.Q(7).addLink(m4BitAdder.B(3));

		for (int i = 7; i >= 0; --i)
			ProbeAdapter.AddProbe(&TestCnt.Q(i));

		for (int i = 3; i >= 0; --i)
			ProbeAdapter.AddProbe(&m4BitAdder.Sum(i));

		GND.setName("GND");
		CntReset.setName("CntReset");
		GND.addLink( m4BitAdder.Cin());
		CntReset.addLink(TestCnt.MR());

		GND.setOutEvent(0, 0);
		CntReset.setOutEvent(0, 0);
	}
private:
	csLogicOut GND;
	csLogicOut CntReset;
	cs4BitAdder m4BitAdder;
	csRippleCnt<8> TestCnt;
};
csTest4BitAdder Test4BitAdder;

int main()
{
	//csTestRippleCount TestRippleCount;
	//csTestFrqDouble TestFrqDouble;

	//TestRippleCount.Start(100,1500);
	//TestFrqDouble.Start(100, 500);
	Test4BitAdder.Start(200, 51400);
}


