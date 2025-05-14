#pragma once
#include "LogicCell.h"

class csClock : public csLogicCell {
public:

	csClock(csEventList& EventList) :
		mOutY(EventList),
		mTriggerInp(this),
		mPeriode_ns(0),
		mHighPeriode(0),
		mLowPeriode(0),
		mStatus(0) 
	{
		setName("CLK");
	}
	void setName(std::string name) {
		mOutY.setName(name + ".Y");
		mTriggerInp.setName(name + ".I");
	}

	void Start(int periode_ns) {
		mPeriode_ns = periode_ns;
		mHighPeriode = periode_ns / 2;
		mLowPeriode = periode_ns / 2;
		mStatus = 0;
		mOutY.addLink(&mTriggerInp);
		AnyInputChanged();
	}

	csLogicInp* TriggerInp() { return &mTriggerInp; }
	csLogicOut& OutY() { return mOutY; }

private:
	virtual void AnyInputChanged() override {
		if (mStatus == 0) {
			mOutY.setOutEvent(mLowPeriode, 1);
			mStatus = 1;
		} else {
			mOutY.setOutEvent(mHighPeriode, 0);
			mStatus = 0;
		}
	}

	csLogicInp mTriggerInp;
	csLogicOut mOutY;

	long mPeriode_ns;
	long mHighPeriode;
	long mLowPeriode;
	int mStatus;
};
