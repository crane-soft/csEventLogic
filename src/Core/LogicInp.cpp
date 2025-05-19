#include "LogicInp.h"
#include "LogicCell.h"

csLogicInp::csLogicInp() {
	mParentCell = 0;
	InpValue = 0;
	mChangedTime = 0;
	mInvert = false;
}

csLogicInp::csLogicInp(csLogicCell* parent) {
	mParentCell = parent;
	InpValue = 0;
	mChangedTime = 0;
	mInvert = false;
}

void csLogicInp::setParentCell(csLogicCell* parent) {
	mParentCell = parent;
}

void csLogicInp::Invert(bool Inv) { 
	mInvert = Inv; 
}

void csLogicInp::setInput(int Value, long EvTime) {
	if (mInvert) {
		Value = Value ^ 1;
	}
	if (Value != InpValue) {
		InpValue = Value;
		mChangedTime = EvTime;
		InputChanged(InpValue);
	}
}

void csLogicInp::InputChanged(int newValue) {
	if (mParentCell)
		mParentCell->AnyInputChanged();
}

