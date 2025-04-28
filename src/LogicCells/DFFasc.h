#pragma once
#include "LogicCell.h"

// D Flip-Flop with rising edge clock and
// low level async set and clear  (74LS74)
class csDFFasc : public csLogicCell
{
public:
	csDFFasc() :
		mClockInp(this),
		mPresetInp(this),
		mClearInp(this),
		mDataInp(this) {
	}

	void setName(std::string name) {
		mOutQ.setName(name + ".Q");
		mNotQ.setName(name + ".N");
	}

	csLogicInp* ClockInp() { return &mClockInp; }
	csLogicInp* PresetInp() { return &mPresetInp; }
	csLogicInp* ClearInp() { return &mClearInp; }
	csLogicInp* DataInp() { return &mDataInp; }

	csLogicOut& OutQ() { return mOutQ; }
	csLogicOut& NotQ() { return mNotQ; }

private:
	void setClockInp(int newValue) {
		if ((newValue == 1) 	// rising edge
			&& (mPresetInp.InpValue == 1)
			&& (mClearInp.InpValue == 1)) {
			int DataInp = mDataInp.InpValue;
			
			// TODO check setup time via mDataInp.mChangedTime
			mOutQ.setOutEvent(5, DataInp);
			mNotQ.setOutEvent(5, DataInp ^1);
		}
	}

	void setPresetInp(int newValue) {
		if ((newValue == 0) 	// low active
			&& (mClearInp.InpValue == 1)) {
			mOutQ.setOutEvent(5, 1);
			mNotQ.setOutEvent(5, 0);
		}
	}

	void setClearInp(int newValue) {
		if ((newValue == 0) 	// low active
			&& (mPresetInp.InpValue == 1)) {
			mOutQ.setOutEvent(5, 0);
			mNotQ.setOutEvent(5, 1);
		}
	}

	INP_OVRIDE(csDFFasc, ClockInp) mClockInp;
	INP_OVRIDE(csDFFasc, PresetInp) mPresetInp;
	INP_OVRIDE(csDFFasc, ClearInp) mClearInp;

	csLogicInp mDataInp;
	csLogicOut mOutQ;
	csLogicOut mNotQ;

};
