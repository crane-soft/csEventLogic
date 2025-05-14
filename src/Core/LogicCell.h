#pragma once
#include "LogicInp.h"
#include "LogicOut.h"

class csLogicCell
{
public:
	csLogicCell() {}
	virtual void AnyInputChanged() {}

	void setParentCells(std::initializer_list<csLogicInp*> list) {
		for (csLogicInp* elem : list) {
			elem->setParentCell(this);
		}
	}
};
