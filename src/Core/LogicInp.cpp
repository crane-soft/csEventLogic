#include "LogicInp.h"
#include "LogicCell.h"

csLogicInp::csLogicInp() {
	mParentCell = 0;
	InpValue = 0;
	mChangedTime = 0;
}

csLogicInp::csLogicInp(csLogicCell* parent) {
	mParentCell = parent;
	InpValue = 0;
	mChangedTime = 0;
}

void csLogicInp::setParentCell(csLogicCell* parent) {
	mParentCell = parent;
}

void csLogicInp::setInput(int Value, long EvTime) {
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

