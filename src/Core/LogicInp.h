#pragma once
#include "csLink.h"
class csLogicCell;


class csLogicInp : public csLink {
public:
	csLogicInp();
	csLogicInp(csLogicCell* parent);
	void setParentCell(csLogicCell* parent);

	void Invert(bool Inv = true);
	void setInput(int Value, long EvTime);
	int InpValue;

protected:
	virtual void InputChanged(int newValue);
	csLogicCell *mParentCell;
	long mChangedTime;
private:
	bool mInvert;
};

