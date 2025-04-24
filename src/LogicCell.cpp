#include "LogicCell.h"
#include "LogicOut.h"

void csAndGate::setName(std::string name) {
	mOutY.setName(name + ".Y");
}

void csAndGate::AnyInputChanged() {
	int inA = mInpA.InpValue;
	int inB = mInpB.InpValue;
	int out = inA & inB;
	mOutY.setOutEvent(5, out);
}

void csTFFac::setName(std::string name) {
	mOutQ.setName(name + ".Q");
	mNotQ.setName(name + ".N");
}

void csTFFac::csToggleInp::InputChanged(int newValue) {
	csTFFac* ffCell = (csTFFac*)mParentCell;
	ffCell->setToggleInp(newValue);
}

void csTFFac::csClearInp::InputChanged(int newValue) {
	csTFFac* ffCell = (csTFFac*)mParentCell;
	ffCell->setClearInput(newValue);
}

void csTFFac::setToggleInp(int newValue) {
	if ((newValue == 0) && (mClearInp.InpValue == 0)) {
		// Toggle at high to low
		int outValue = mOutQ.OutValue() ^ 1;
		mOutQ.setOutEvent(9, outValue);
		//mNotQ.setOutEvent(9, outValue ^ 1);
	}
}

void csTFFac::setClearInput(int newValue) {
	// async clear active high input
	if (newValue == 1) {
		mOutQ.setOutEvent(5, 0);
		//mNotQ.setOutEvent(5, 1);
	}
}


void csClock::Start(int periode_ns) {
	mPeriode_ns = periode_ns;
	mHighPeriode = periode_ns / 2;
	mLowPeriode = periode_ns / 2;
	mStatus = 0;
	mOutY.addLink(&mTriggerInp);
	AnyInputChanged();
}

void csClock::setName(std::string name) {
	mOutY.setName(name + ".Y");
}

void csClock::AnyInputChanged() {
	if (mStatus == 0) {
		mOutY.setOutEvent(mLowPeriode, 1);
		mStatus = 1;
	} else {
		mOutY.setOutEvent(mHighPeriode, 0);
		mStatus = 0;
	}
}