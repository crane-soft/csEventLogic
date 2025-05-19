#pragma once
#include "LogicCell.h"

#include <stdint.h>
#include <list>
#include <iostream>

class csProbeADapter {
public:
	void AddProbe(csLogicOut* newProbe) {
		ProbeInputs.emplace_back();
		csLogicInp* ProbeInp = &ProbeInputs.back();
		ProbeInp->setName("Probe:"+newProbe->Name());
		newProbe->addLink(ProbeInp);
	}

	void AddProbes(std::initializer_list<csLogicOut*> list) {
		for (csLogicOut* elem : list) {
			AddProbe(elem);
		}
	}

	void printStatusBits() {
		for (csLogicInp const &ProbeInp : ProbeInputs) {
			std::cout << ProbeInp.InpValue;
		}
	}

	uint32_t StatusBits() {
		uint32_t bits = 0;
		for (csLogicInp const& ProbeInp : ProbeInputs) {
			bits = bits << 1 | (ProbeInp.InpValue & 1);
		}
		return bits;
	}
	std::string StatusBitStr() {
		std::string bitStr;
		for (csLogicInp const& ProbeInp : ProbeInputs) {
			bitStr += ProbeInp.InpValue ? '1' : '0';
		}
		return bitStr;
	}
private:
	std::list<csLogicInp> ProbeInputs;
};
