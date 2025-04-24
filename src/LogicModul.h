#pragma once
#include "LogicCell.h"

class cs4BitRippleCnt {
public:
	cs4BitRippleCnt(csEventList& EventList) :
		TFF0(EventList),
		TFF1(EventList),
		TFF2(EventList),
		TFF3(EventList)
	{
		TFF0.setName("TFF0");
		TFF1.setName("TFF1");
		TFF2.setName("TFF2");
		TFF3.setName("TFF3");

		TFF0.OutQ().addLink(TFF1.ToggleInp());
		TFF1.OutQ().addLink(TFF2.ToggleInp());
		TFF2.OutQ().addLink(TFF3.ToggleInp());

		TFF0.ClearInp()->addLinks({ TFF1.ClearInp(),TFF2.ClearInp(),TFF3.ClearInp() });


	}
	csLogicInp* CP() { return TFF0.ToggleInp(); }
	csLogicInp* MR() { return TFF0.ClearInp(); }

	csLogicOut& Q0() { return TFF0.OutQ(); }
	csLogicOut& Q1() { return TFF1.OutQ(); }
	csLogicOut& Q2() { return TFF2.OutQ(); }
	csLogicOut& Q3() { return TFF3.OutQ(); }

private:
	csTFFac TFF0, TFF1, TFF2, TFF3;
};