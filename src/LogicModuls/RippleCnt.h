#pragma once
#include "TFFac.h"
#include <format>
#include <array>
#include <utility>

template<const int CntWidth>
class csRippleCnt {
public:
	csRippleCnt(csEventList& EventList) :
		csRippleCnt(EventList,std::make_index_sequence<CntWidth>{})
	{
		setName("CNT");
		for (int i = 1; i < CntWidth; ++i) {
			TFF[i-1].OutQ().addLink(TFF[i].ToggleInp());
			TFF[0].ClearInp()->addLink(TFF[i].ClearInp());
		}
	}
	void setName(std::string name) {
		for (int i = 0; i < CntWidth; ++i) {
			std::string FFname = std::format("{}.FF{}", name, i);
			TFF[i].setName(FFname);
			TFF[i].ClearInp()->setName(FFname + ".R");
			TFF[i].ToggleInp()->setName(FFname + ".T");
		}
	}
	csLogicInp* CP() { return TFF[0].ToggleInp(); }
	csLogicInp* MR() { return TFF[0].ClearInp(); }

	csLogicOut& Q(int No) { return TFF[No].OutQ(); }

private:
	template <std::size_t... Is>
	explicit csRippleCnt(csEventList& EventList, std::index_sequence<Is...>) : TFF{ (Is, EventList)... } {}
	std::array<csTFFac, CntWidth> TFF;
};
