#pragma once
#include "LogicGate.h"

class csFrqDoubler
{
public:
	csFrqDoubler() {
		mXor.Inp(0)->addLink(mDelay.Inp());
		mDelay.OutY().addLink(mXor.Inp(1));
	}
	csLogicInp* CP() { return mXor.Inp(0); }
	csLogicOut& OutY() { return mXor.OutY(); }
private:
	csXorGate<> mXor;	
	csDelayGate mDelay;
};
