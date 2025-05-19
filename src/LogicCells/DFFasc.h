#pragma once
#include "LogicCell.h"

// D Flip-Flop with rising edge clock and
// low level async set and clear  (74LS74)
class csDFFasc : public csLogicCell
{
public:
	csDFFasc(csEventList* EventList) :
		mOutQ(EventList),
		mNotQ(EventList)
	{
		setParentCells({ &mClockInp,&mPresetInp,&mClearInp,&mDataInp });
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

	class csClockInp : public csLogicInp {
		void InputChanged(int newValue) override {
			reinterpret_cast<csDFFasc*>(mParentCell)->setClockInp(newValue);
		}
	} mClockInp;

	class csPresetInp : public csLogicInp {
		void InputChanged(int newValue) override {
			reinterpret_cast<csDFFasc*>(mParentCell)->setPresetInp(newValue);
		}
	} mPresetInp;

	class csClearInp : public csLogicInp {
		void InputChanged(int newValue) override {
			reinterpret_cast<csDFFasc*>(mParentCell)->setClearInp(newValue);
		}
	} mClearInp;

	csLogicInp mDataInp;
	csLogicOut mOutQ;
	csLogicOut mNotQ;

};
