#include "LogicInp.h"
#include "LogicCell.h"

csLogicInp::csLogicInp(csLogicCell* parent) {
	mParentCell = parent;
	mNextConnection = 0;
	InpValue = 0;
}

void csLogicInp::setInput(int Value) {
	if (Value != InpValue) {
		InpValue = Value;
		InputChanged(InpValue);
	}
}

void csLogicInp::InputChanged(int newValue) {
	mParentCell->AnyInputChanged();
}

void csLogicInp::setNextConnection(csLogicInp* nextCon) {
	mNextConnection = nextCon;
}
