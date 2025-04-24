#include "LogicOut.h"
#include "LogicInp.h"

#include <iostream>

csLogicOut::csLogicOut(csEventList& EventList) :
	mEvents(EventList) 
{
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
	if (mNextLink != 0) {
		for (csLink * iLink = mNextLink; iLink != 0; iLink = iLink->NextLink()) {
			csLogicInp* LogicInp = (csLogicInp*)iLink;
			LogicInp->setInput(mOutValue);
		}
	}
}

int csLogicOut::OutValue() const {
	return mOutValue;
}

