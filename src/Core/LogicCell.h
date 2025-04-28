#pragma once
#include "LogicInp.h"
#include "LogicOut.h"

class csLogicCell
{
public:
	csLogicCell() {}
	virtual void AnyInputChanged() {}

};

// Macro use to generate specialised InputChanged() override
#define INP_OVRIDE(CellClass,INPFUNC) \
	class cs ## INPFUNC : public csLogicInp { \
		public: \
		cs ## INPFUNC(csLogicCell* parent) : csLogicInp(parent) {} \
		void InputChanged(int newValue) override { \
			CellClass* ffCell = (CellClass*)mParentCell; \
			ffCell->set ## INPFUNC(newValue); \
		}}
