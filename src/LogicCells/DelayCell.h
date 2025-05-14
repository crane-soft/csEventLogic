#pragma once
#include "LogicCell.h"

class csDelayCell : public csLogicCell
{
public:
	csDelayCell(csEventList& EventList, int Delay = 5) :
		mOutY(EventList),
		mInp(this),
		mDelay(Delay) {
		setName("DEL");
	}

	void setDelay(int Delay) {
		mDelay = Delay;
	}
	void setName(std::string name) {
		mOutY.setName(name + ".Y");
		mInp.setName(name + ".I");
	}

	csLogicInp* Inp() { return &mInp; }
	csLogicOut& OutY() { return mOutY; }

protected:
	virtual void AnyInputChanged() override {
		int out = mInp.InpValue;
		mOutY.setOutEvent(mDelay, out);
	}

	int mDelay;
	csLogicOut mOutY;
	csLogicInp mInp;
};
