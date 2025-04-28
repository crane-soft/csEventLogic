#include "LogicCell.h"
#include "LogicGate.h"
#include "Clock.h"
#include "TFFac.h"
#include "LogicOut.h"
#include "EventList.h"
#include "RippleCnt.h"
#include "FrqDoubler.h"

#include <iostream>
#include <iomanip>

csEventList	csLogicOut::EventList;
csClock InpClock;
csAndGate AndGate;
csXorGate XorGate;

cs4BitRippleCnt<4> RippleCnt;

void printLog(long EvTime, csLogicOut* LogicOut) {

	std::cout << "EV:" << std::setw(4) << EvTime
		<< std::setw(7) << LogicOut->OutName() 
		<< "=" << LogicOut->OutValue();
}

void printStatus() {
	std::cout << " ";
	for (int i = 3; i >= 0; --i)
		std::cout << RippleCnt.Q(i).OutValue();
	std::cout << " " << AndGate.OutY().OutValue() << "\n";
}

void TestRippleCount()
{
	InpClock.OutY().addLink(RippleCnt.CP());
	RippleCnt.Q(2).addLink(AndGate.Inp(0));
	RippleCnt.Q(3).addLink(AndGate.Inp(1));
	AndGate.OutY().addLink(RippleCnt.MR());

	InpClock.Start(100);	// 100 ns = 10 MHz

	csEvent* NextEvent;
	while ((NextEvent = csLogicOut::EventList.TakeRootEvent()) != 0 ) {
		long EventTime = NextEvent->EventTime();
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		printLog(EventTime, LogicOut);
		printStatus();
	}
}


void TestFrqDouble() 
{
	csFrqDoubler FrqDoubler;
	csDelayGate DblFrqOut;

	InpClock.OutY().addLink(FrqDoubler.CP());
	FrqDoubler.OutY().addLink(DblFrqOut.Inp());
	InpClock.Start(100);

	csEvent* NextEvent;
	while ((NextEvent = csLogicOut::EventList.TakeRootEvent()) != 0) {
		long EventTime = NextEvent->EventTime();
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		printLog(EventTime, LogicOut);
		std::cout << "\n";
	}
}
int main()
{
	//TestRippleCount();
	TestFrqDouble();
}


