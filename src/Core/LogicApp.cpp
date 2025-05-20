#include "LogicApp.h"
#include <iostream>
#include <iomanip>
#include <format>
void csLogicApp::printEvenLog(long EvTime, csLogicOut* LogicOut) 
{
	std::cout << "EV:" << std::setw(4) << EvTime
		<< std::setw(15) << LogicOut->Name()
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
	int errCnt = 0;
	int dbgStatus = 0;
	while ((NextEvent = EventList.TakeRootEvent()) != 0) {
		long EventTime = NextEvent->EventTime();
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		
		bool ClkRisingEdge = MainClock.risingEdge();
		if (ClkRisingEdge || dbgStatus) {
			printEvenLog(EventTime, LogicOut);
			std::cout << " " << ProbeAdapter.StatusBitStr();
			uint32_t ProbeBits = ProbeAdapter.StatusBits();
			unsigned InpB = (ProbeBits >> 8) & 0x0f;
			unsigned InpA = (ProbeBits >> 4) & 0x0f;
			unsigned Sum = ProbeBits  & 0x0f;

			std::cout << std::format(" {} {} {}",InpB, InpA,Sum);
			if (ClkRisingEdge) {
				if (((InpA + InpB) & 0x0f) != Sum) {
					++errCnt;
					std::cout << " error:" << errCnt;
				} else {
					std::cout << " OK";
				}
			} else {
				std::cout << " -";
			}
			std::cout << "\r\n";
		}
		if (mMaxTime > 0) {
			if (EventTime > mMaxTime)
				break;
		}
	}
}
