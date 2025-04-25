#pragma once
#include "LogicCell.h"

class csAndGate : public csLogicCell
{
public:
	csAndGate() :
		mInpA(this),
		mInpB(this) 
	{
		setName ("AND");
	}
	void setName(std::string name) {
		mOutY.setName(name + ".Y");
	}

	csLogicInp* InpA() { return &mInpA; }
	csLogicInp* InpB() { return &mInpB; }
	csLogicOut& OutY() { return mOutY; }
private:
	virtual void AnyInputChanged() override {
		int inA = mInpA.InpValue;
		int inB = mInpB.InpValue;
		int out = inA & inB;
		mOutY.setOutEvent(5, out);
	}

	csLogicInp mInpA;
	csLogicInp mInpB;
	csLogicOut mOutY;
	csLogicInp* InpList[2] = { &mInpA,&mInpB };
	csLogicOut* OutList[1] = { &mOutY };
};

