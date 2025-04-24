#include "LogicCell.h"
#include "LogicOut.h"
#include "EventList.h"
#include "LogicModul.h"

#include <iostream>
#include <iomanip>

csEventList EventList;
csClock InpClock(EventList);
cs4BitRippleCnt RippleCnt(EventList);
csAndGate AndGate(EventList);

void BuilsNetlist()
{
	InpClock.setName(" CLK");
	AndGate.setName(" AND");

	InpClock.OutY().addLink(RippleCnt.CP());
	RippleCnt.Q2().addLink(AndGate.InpA());
	RippleCnt.Q3().addLink(AndGate.InpB());
	AndGate.OutY().addLink(RippleCnt.MR());

	InpClock.Start(100);	// 100 ns = 10 MHz

	csEvent* NextEvent;
	while ((NextEvent = EventList.TakeRootEvent()) != 0 ) {
		std::cout << "EV:" << std::setw(4) << NextEvent->EventTime() << " ";
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		std::cout << " "
			<< RippleCnt.Q3().OutValue()
			<< RippleCnt.Q2().OutValue()
			<< RippleCnt.Q1().OutValue()
			<< RippleCnt.Q0().OutValue()
			<< " " << AndGate.OutY().OutValue()
			<< "\n";
	}
}

int main()
{
	BuilsNetlist();
}


