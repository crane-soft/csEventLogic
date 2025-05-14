#pragma once
#include "LogicCell.h"

#include <list>
#include <iostream>

class csProbeADapter {
public:
	void AddProbe(csLogicOut* newProbe) {
		ProbeInputs.emplace_back();
		newProbe->addLink(&ProbeInputs.back());
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
