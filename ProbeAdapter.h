#pragma once
#include "LogicCell.h"

class csProbeADapter {
public:
	void AddProbe(csLogicOut* newProbe) {
		csLogicInp* ProbInp = new csLogicInp();
		newProbe->addLink(ProbInp);
	}
private:
	csLink ProbeInputs;
};