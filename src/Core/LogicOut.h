#pragma once
#include "EventList.h"
#include "csLink.h"
#include <string>
class csLogicInp;

class csLogicOut : public csLink, protected csEvent
{
public:
	csLogicOut(csEventList* EventList = 0);
	void setEventList(csEventList* EventList) { mEventList = EventList; }
	void setOutEvent(int delay, int newValue);
	void UpdateOutput();
	int OutValue() const;

private:
	int mNewValue;
	int mOutValue;
	csEventList *mEventList;
};

