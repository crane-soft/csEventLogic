#pragma once
#include "LogicCell.h"

// Toggle flip-flop with negative clock high level async clear (7493)
class csTFFac : public csLogicCell
{
public:
	csTFFac() :
		mToggleInp(this),
		mClearInp(this) {
	}

	void setName(std::string name) {
		mOutQ.setName(name + ".Q");
		mNotQ.setName(name + ".N");
	}

	csLogicInp* ToggleInp() { return &mToggleInp; }
	csLogicInp* ClearInp() { return &mClearInp; }
	csLogicOut& OutQ() { return mOutQ; }
	csLogicOut& NotQ() { return mNotQ; }


private:
	void setToggleInp(int newValue) {
		if ((newValue == 0) && (mClearInp.InpValue == 0)) {
			// Toggle at high to low
			int outValue = mOutQ.OutValue() ^ 1;
			mOutQ.setOutEvent(9, outValue);
			mNotQ.setOutEvent(9, outValue ^ 1);
		}
	}

	void setClearInp(int newValue) {
		// async clear active high input
		if (newValue == 1) {
			mOutQ.setOutEvent(5, 0);
			mNotQ.setOutEvent(5, 1);
		}
	}

	INP_OVRIDE(csTFFac, ToggleInp) mToggleInp;
	INP_OVRIDE(csTFFac, ClearInp)  mClearInp;

	csLogicOut mOutQ;
	csLogicOut mNotQ;
};
