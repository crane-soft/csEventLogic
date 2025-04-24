#pragma once
#include "LogicInp.h"
#include "LogicOut.h"

class csLogicCell
{
public:
	csLogicCell() {}
	virtual void AnyInputChanged() {}
};

class csAndGate : public csLogicCell
{
public:
	csAndGate(csEventList& EventList):
		mInpA(this),
		mInpB(this),
		mOutY(EventList)
	{
	}
	void setName(std::string name);

	csLogicInp* InpA() { return &mInpA;	}
	csLogicInp* InpB() { return &mInpB; }
	csLogicOut& OutY() { return mOutY; }
private:
	virtual void AnyInputChanged() override;
	csLogicInp mInpA;
	csLogicInp mInpB;
	csLogicOut mOutY;
	csLogicInp* InpList[2] = { &mInpA,&mInpB };
	csLogicOut* OutList[1] = { &mOutY };
};

class csTFFac : public csLogicCell
{
public:

	csTFFac(csEventList& EventList) :
		mToggleInp(this),
		mClearInp(this),
		mOutQ(EventList),
		mNotQ(EventList)
	{}
	void setName(std::string name);

	csLogicInp* ToggleInp()  { return &mToggleInp; }
	csLogicInp* ClearInp()  { return &mClearInp; }
	csLogicOut& OutQ() { return mOutQ; }
	csLogicOut& NotQ() { return mNotQ; }

	void setToggleInp(int newValue);
	void setClearInput(int newValue);

private:
	class csToggleInp : public csLogicInp {
	public : 
		csToggleInp(csLogicCell* parent) : csLogicInp(parent) {}
		void InputChanged(int newValue) override;
	} mToggleInp;

	class csClearInp : public csLogicInp {
	public:
		csClearInp(csLogicCell* parent) : csLogicInp(parent) {}
		void InputChanged(int newValue) override;
	} mClearInp;

	csLogicOut mOutQ;
	csLogicOut mNotQ;
};

class csClock : public csLogicCell {
public:

	csClock(csEventList& EventList) :
		mTriggerInp(this),
		mOutY(EventList),
		mPeriode_ns(0),
		mHighPeriode(0),
		mLowPeriode(0),
		mStatus(0)
	{}
	void setName(std::string name);

	void Start(int periode_ns);
	csLogicInp* TriggerInp() { return &mTriggerInp; }
	csLogicOut& OutY() { return mOutY; }

private:
	virtual void AnyInputChanged() override;

	csLogicInp mTriggerInp;
	csLogicOut mOutY;

	long mPeriode_ns;
	long mHighPeriode;
	long mLowPeriode;
	int mStatus;
};