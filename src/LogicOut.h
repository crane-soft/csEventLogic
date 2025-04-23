#pragma once
#include "EventList.h"
#include <string>
class csLogicInp;

class csLogicOut : protected csEvent
{
public:
	csLogicOut(csEventList& EventList);
	void setName(std::string name) {mOutName = name;}
	void setOutEvent(int delay, int newValue);
	void UpdateOutput();
	int OutValue() const;
	void AddConnection(csLogicInp* InpWire);

private:
	csEventList &mEvents;
	csLogicInp* mWire;
	csLogicInp* mLastWire;

	int mNewValue;
	int mOutValue;
	std::string mOutName;
};

