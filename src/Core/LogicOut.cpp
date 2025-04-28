#include "LogicOut.h"
#include "LogicInp.h"

#include <iostream>
#include <iomanip>

csLogicOut::csLogicOut() 
{
	mOutValue = 0;
	mNewValue = -1;	// need for first change event
	mOutName = "nc";
}

void csLogicOut::setOutEvent(int delay, int newValue) {
	if (newValue != mNewValue) {
		mNewValue = newValue;
		if (mNextLink != 0) {
			EventList.InsertEvent(this, delay);
		}
	}
}

void csLogicOut::UpdateOutput() {
	mOutValue = mNewValue;
	if (mNextLink != 0) {
		for (csLink * iLink = mNextLink; iLink != 0; iLink = iLink->NextLink()) {
			csLogicInp* LogicInp = (csLogicInp*)iLink;
			LogicInp->setInput(mOutValue, EventTime());
		}
	}
}

int csLogicOut::OutValue() const {
	return mOutValue;
}

