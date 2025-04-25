#pragma once
#include "csLink.h"
class csLogicCell;


class csLogicInp : public csLink {
public:
	csLogicInp(csLogicCell* parent);
	void setInput(int Value);
	int InpValue;

protected:
	virtual void InputChanged(int newValue);
	csLogicCell *mParentCell;
};

