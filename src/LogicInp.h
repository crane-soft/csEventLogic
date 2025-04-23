#pragma once
class csLogicCell;

class csLogicInp {
public:
	csLogicInp(csLogicCell* parent);
	void setInput(int Value);

	void setNextConnection(csLogicInp* nextCon);
	csLogicInp* NextConnection() { return mNextConnection; }
	int InpValue;
protected:
	virtual void InputChanged(int newValue);
	csLogicCell *mParentCell;
private:
	csLogicInp* mNextConnection;

};

