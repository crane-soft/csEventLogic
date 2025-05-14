#pragma once
#include "EventList.h"
#include "Clock.h"
#include "ProbeAdapter.h"

class csLogicApp
{
public:
	csLogicApp() : 
		MainClock(EventList)
	{}
	csClock MainClock;
	csEventList	EventList;
	csProbeADapter ProbeAdapter;

	void Start(int periode_ns, int until_ns = 0);
	void Run();
	void printEvenLog(long EvTime, csLogicOut* LogicOut);

private:
	int mMaxTime = 0;
};

