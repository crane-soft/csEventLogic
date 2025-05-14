#include "LogicApp.h"
#include <iostream>
#include <iomanip>

void csLogicApp::printEvenLog(long EvTime, csLogicOut* LogicOut) 
{
	std::cout << "EV:" << std::setw(4) << EvTime
		<< std::setw(11) << LogicOut->Name()
		<< "=" << LogicOut->OutValue();
}

void csLogicApp::Start(int periode_ns, int until_ns)
{
	mMaxTime = until_ns;
	MainClock.Start(periode_ns);
	Run();
}

void csLogicApp::Run() 
{
	csEvent* NextEvent;
	while ((NextEvent = EventList.TakeRootEvent()) != 0) {
		long EventTime = NextEvent->EventTime();
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		printEvenLog(EventTime, LogicOut);
		std::cout << " " << ProbeAdapter.StatusBitStr() << "\n";
		if (mMaxTime > 0) {
			if (EventTime > mMaxTime)
				break;
		}
	}
}
