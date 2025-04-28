#pragma once
#include "LogicCell.h"
#include <vector>
#include <format>

typedef int (*LogicFunc_t)(int A, int B);
inline int  AndFunc  (int A, int B)  {return A & B;}
inline int  NandFunc (int A, int B) { return (A & B)^1; }
inline int  OrFunc   (int A, int B) { return A | B; }
inline int  NorFunc  (int A, int B) { return (A | B) ^ 1; }
inline int  XorFunc  (int A, int B) { return A ^ B; }

template<const int NumInp, const LogicFunc_t LogicFunc>
class csLogicGate : public csLogicCell
{
public:
	csLogicGate(std::string name) {
		for (int i = 0; i < NumInp; ++i) {
			mInp[i].setParentCell(this);
		}
		setName(name);
	}

	void setName(std::string name) {
		mOutY.setName(name + ".Y");
		for (int i = 0; i < NumInp; ++i) {
			mInp[i].setName(std::format("{}.IN{}", name, i));
		}
	}

	csLogicInp* Inp(int No) { return &mInp[No]; }
	csLogicOut& OutY() { return mOutY; }

protected:
	virtual void AnyInputChanged() override {
		int out = mInp[0].InpValue;
		for (int i = 1; i < NumInp; ++i) {
			out = LogicFunc(out, mInp[i].InpValue);
		}
		mOutY.setOutEvent(5, out);
	}

	csLogicOut mOutY;
	csLogicInp mInp[NumInp];
};


#define DEF_LOGIC_GATE(LOG)	\
template<const int NumInp = 2> \
class cs ##LOG## Gate : public csLogicGate<NumInp, LOG##Func> { \
public: cs ## LOG## Gate() : csLogicGate<NumInp, LOG##Func>(#LOG) {}};

DEF_LOGIC_GATE(And)
DEF_LOGIC_GATE(Or)
//DEF_LOGIC_GATE(Xor)


template<const int NumInp = 2> 
class csXorGate : public csLogicGate<NumInp, XorFunc>{ 
public: csXorGate() : csLogicGate<NumInp, XorFunc>("XOR") {} };

class csDelayGate : public csLogicCell
{
public:
	csDelayGate(int Delay = 5) : 
		mInp(this),
		mDelay(Delay)
	{
		setName("DEL");
	}

	void setDelay(int Delay) {
		mDelay = Delay;
	}
	void setName(std::string name) {
		mOutY.setName(name + ".Y");
		mInp.setName(name + ".I");
	}

	csLogicInp* Inp() { return &mInp; }
	csLogicOut& OutY() { return mOutY; }

protected:
	virtual void AnyInputChanged() override {
		int out = mInp.InpValue;
		mOutY.setOutEvent(mDelay, out);
	}

	int mDelay;
	csLogicOut mOutY;
	csLogicInp mInp;
};
