#include "LogicCell.h"
#include "LogicOut.h"
#include "EventList.h"

void BuilsNetlist() {
	
	csEventList EventList;
	csClock InpClock(EventList);
	csTFFac TFF1(EventList), TFF2(EventList), TFF3(EventList), TFF4(EventList);
	csAndGate AndGate(EventList);

	InpClock.setName(" CLK");
	AndGate.setName(" AND");
	TFF1.setName("TFF1");
	TFF2.setName("TFF2");
	TFF3.setName("TFF3");
	TFF4.setName("TFF4");

	InpClock.OutY().AddConnection(TFF1.ToggleInp());
	TFF1.OutQ().AddConnection(TFF2.ToggleInp());
	TFF2.OutQ().AddConnection(TFF3.ToggleInp());
	TFF3.OutQ().AddConnection(TFF4.ToggleInp());

	TFF3.OutQ().AddConnection(AndGate.InpA());
	TFF4.OutQ().AddConnection(AndGate.InpB());
	AndGate.OutY().AddConnection(TFF1.ClearInp());
	AndGate.OutY().AddConnection(TFF2.ClearInp());
	AndGate.OutY().AddConnection(TFF3.ClearInp());
	AndGate.OutY().AddConnection(TFF4.ClearInp());

	InpClock.Start(100);	// 100 ns = 10 MHz

	csEvent* NextEvent;
	while ((NextEvent = EventList.TakeRootEvent()) != 0 ) {
		csLogicOut* LogicOut = (csLogicOut*)NextEvent;
		LogicOut->UpdateOutput();
		printf(" %d%d%d%d %d\r\n",
			TFF4.OutQ().OutValue(),
			TFF3.OutQ().OutValue(),
			TFF2.OutQ().OutValue(),
			TFF1.OutQ().OutValue(),
			AndGate.OutY().OutValue());
	}
}

int main()
{
	BuilsNetlist();
}


