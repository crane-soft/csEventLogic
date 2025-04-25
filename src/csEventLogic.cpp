#include "LogicCell.h"
#include "AndGate.h"
#include "Clock.h"
#include "TFFac.h"
#include "LogicOut.h"
#include "EventList.h"
#include "RippleCnt.h"

#include <iostream>
#include <iomanip>

csEventList	csLogicOut::EventList;
csClock InpClock;
cs4BitRippleCnt<4> RippleCnt;
csAndGate AndGate;

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

void BuilsNetlist()
{
	InpClock.OutY().addLink(RippleCnt.CP());
	RippleCnt.Q(2).addLink(AndGate.InpA());
	RippleCnt.Q(3).addLink(AndGate.InpB());
	AndGate.OutY().addLink(RippleCnt.MR());

	InpClock.Start(100);	// 100 ns = 10 MHz

	csEvent* NextEvent;
	while ((NextEvent = csLogicOut::EventList.TakeRootEvent()) != 0 ) {
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();

		printLog(NextEvent->EventTime(), LogicOut);
		printStatus();
	}
}

int main()
{
	BuilsNetlist();
}


