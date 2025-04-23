#include "LogicOut.h"
#include "LogicInp.h"

#include <iostream>

csLogicOut::csLogicOut(csEventList& EventList) :
	mEvents(EventList) {
	mWire = 0;
	mLastWire = 0;
	mOutValue = 0;
	mNewValue = -1;	// need for first change event
	mOutName = "nc";
}

void csLogicOut::setOutEvent(int delay, int newValue) {
	if (newValue != mNewValue) {
		mNewValue = newValue;
		mEvents.InsertEvent(this, delay);
	}
}

void csLogicOut::UpdateOutput() {
	mOutValue = mNewValue;
	std::cout << mOutName << "=" << mOutValue;
	if (mWire != 0) {
		for (csLogicInp* LogInp = mWire; LogInp != 0; LogInp = LogInp->NextConnection()) {
			LogInp->setInput(mOutValue);
		}
	}
}

int csLogicOut::OutValue() const {
	return mOutValue;
}
void csLogicOut::AddConnection(csLogicInp* InpWire) {
	if (mWire == 0) {
		mWire = InpWire;
	} else {
		mLastWire->setNextConnection(InpWire);
	}
	mLastWire = InpWire;
}
