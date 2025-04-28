#pragma once
#include "LogicGate.h"

class csFrqDoubler
{
public:
	csFrqDoubler(int Delay = 5) {
		mXor.Inp(0)->addLink(mDelay.Inp());
		mDelay.OutY().addLink(mXor.Inp(1));
		setDelay(Delay);
	}
	void setDelay(int Delay) {
		mDelay.setDelay(Delay);
	}
	csLogicInp* CP() { return mXor.Inp(0); }
	csLogicOut& OutY() { return mXor.OutY(); }
private:
	csXorGate<> mXor;	
	csDelayGate mDelay;
};
