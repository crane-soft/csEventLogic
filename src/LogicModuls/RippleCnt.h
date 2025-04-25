#pragma once
#include "TFFac.h"
#include <format>

template<const int CntWidth>
class cs4BitRippleCnt {
public:
	cs4BitRippleCnt() 
	{
		for (int i = 1; i < CntWidth; ++i) {
			TFF[i-1].OutQ().addLink(TFF[i].ToggleInp());
			TFF[0].ClearInp()->addLink(TFF[i].ClearInp());
		}
		setName("CNT");
	}
	void setName(std::string name) {
		for (int i = 0; i < CntWidth; ++i) {
			TFF[i].setName(std::format("{}{}",name, i));
		}
	}
	csLogicInp* CP() { return TFF[0].ToggleInp(); }
	csLogicInp* MR() { return TFF[0].ClearInp(); }

	csLogicOut& Q(int No) { return TFF[No].OutQ(); }

private:
	csTFFac TFF[CntWidth];
};
