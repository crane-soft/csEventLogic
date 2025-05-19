#pragma once
#include "LogicCell.h"
#include <format>

typedef int (*LogicFunc_t)(int A, int B);
inline int  AndFunc  (int A, int B)  {return A & B;}
inline int  NandFunc (int A, int B) { return (A & B)^1; }
inline int  OrFunc   (int A, int B) { return A | B; }
inline int  NorFunc  (int A, int B) { return (A | B) ^ 1; }
inline int  XorFunc  (int A, int B) { return A ^ B; }

template<const int NumInp, const LogicFunc_t LogicFunc, const bool InvOut = false>
class csLogicGate : public csLogicCell
{
public:
	csLogicGate(std::string name, csEventList* EventList) :
		mOutY(EventList)
	{
		for (int i = 0; i < NumInp; ++i) {
			mInp[i].setParentCell(this);
		}
		setName(name);
	}
	void setEventList(csEventList* EventList) {
		mOutY.setEventList(EventList);
	}

	void setName(std::string name) {
		mOutY.setName(name + ".Y");
		for (int i = 0; i < NumInp; ++i) {
			mInp[i].setName(std::format("{}.IN{}", name, i));
		}
	}

	void InvertInp(int No) { mInp[No].Invert(); }
	csLogicInp* Inp(int No) { return &mInp[No]; }
	csLogicOut& OutY() { return mOutY; }

protected:
	virtual void AnyInputChanged() override {
		int out = mInp[0].InpValue;
		for (int i = 1; i < NumInp; ++i) {
			out = LogicFunc(out, mInp[i].InpValue);
		}
		if (InvOut) {
			out = out ^ 1;
		}
		mOutY.setOutEvent(5, out);
	}

	csLogicOut mOutY;
	csLogicInp mInp[NumInp];
};


template<const int NumInp = 2>
class csAndGate : public csLogicGate<NumInp, AndFunc> 
{
public: 
	csAndGate(csEventList* EventList = 0) :
		csLogicGate<NumInp, AndFunc>("And", EventList) {}
};

template<const int NumInp = 2> 
class csNandGate : public csLogicGate<NumInp, AndFunc, true> 
{ 
public: 
	csNandGate(csEventList* EventList = 0) : 
		csLogicGate<NumInp, AndFunc, true>("Nand", EventList)	{} 
};

template<const int NumInp = 2>
class csOrGate : public csLogicGate<NumInp, OrFunc>
{
public:
	csOrGate(csEventList* EventList = 0) :
		csLogicGate<NumInp, OrFunc>("Or", EventList) {}
};

template<const int NumInp = 2>
class csNorGate : public csLogicGate<NumInp, OrFunc, true>
{
public:
	csNorGate(csEventList* EventList = 0) :
		csLogicGate<NumInp, OrFunc, true>("Nor", EventList) {}
};

template<const int NumInp = 2>
class csXorGate : public csLogicGate<NumInp, XorFunc>
{
public:
	csXorGate(csEventList* EventList = 0) :
		csLogicGate<NumInp, XorFunc>("Xor", EventList) {}
};

template<const int NumInp = 2>
class csXnorGate : public csLogicGate<NumInp, XorFunc, true>
{
public:
	csXnorGate(csEventList* EventList = 0) :
		csLogicGate<NumInp, XorFunc, true>("Xnor", EventList) {}
};
