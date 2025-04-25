#pragma once
#include "EventList.h"
#include "csLink.h"
#include <string>
class csLogicInp;

class csLogicOut : public csLink, protected csEvent
{
public:
	csLogicOut();
	void setName(std::string name) {mOutName = name;}
	void setOutEvent(int delay, int newValue);
	void UpdateOutput();
	int OutValue() const;
	std::string OutName() { return mOutName; }
	static csEventList EventList;

private:
	int mNewValue;
	int mOutValue;
	std::string mOutName;
};

