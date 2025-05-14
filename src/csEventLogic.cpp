
#include "LogicGate.h"
#include "RippleCnt.h"
#include "FrqDoubler.h"
#include "LogicApp.h"

class csTestRippleCount : public csLogicApp
{
public:
	csTestRippleCount() :
		RippleCnt(EventList),
		AndGate(EventList)
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
		FrqDoubler(EventList, 15)
	{
		MainClock.OutY().addLink(FrqDoubler.CP());
		ProbeAdapter.AddProbes({ &MainClock.OutY(),&FrqDoubler.OutY() });
	}
private:
	csFrqDoubler FrqDoubler;
};

int main()
{
	csTestRippleCount TestRippleCount;
	csTestFrqDouble TestFrqDouble;

	//TestRippleCount.Start(100,1500);
	TestFrqDouble.Start(100, 500);
}


