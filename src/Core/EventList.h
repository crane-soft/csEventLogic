#pragma once
class csLogicOut;
class csEvent {
public:
	csEvent() {
		mPending = false;
		mEventTime_ns = 0;
		mNextEvent = 0;
	}

	void InsertAfter(csEvent* newEvent) {
		csEvent* prevNextEv = mNextEvent;
		mNextEvent = newEvent;
		newEvent->setNextEvent(prevNextEv);
	}

	void setEventTime(long EventTime) {
		mEventTime_ns = EventTime;
	}

	long EventTime() const {
		return mEventTime_ns;
	}
	csEvent* NextEvent() const {
		return mNextEvent;
	}

	void setNextEvent(csEvent* nextEvent) {
		mNextEvent = nextEvent;
	}

	void setPending() {
		mPending = true;
	}
	bool Pending() {
		return mPending;
	}
	void Clear() {
		mPending = false;
		mNextEvent = 0;
	}

protected:
	bool mPending;
	long mEventTime_ns;
	csEvent* mNextEvent;
};

class csEventList
{
public:
	csEventList();
	void InsertEvent(csEvent* newEvent, int delay);
	void InsertFront(csEvent* newEvent);
	csEvent* TakeRootEvent();
	void RemoveEvent(csEvent* Event);
private:
	long mCurrentTime_ns;
	csEvent * mEventsRoot;
};
