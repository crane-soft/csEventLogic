#pragma once

class csEvent {
public:
	csEvent() {
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
	void Clear() {
		mNextEvent = 0;
	}

private:
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

private:
	long mCurrentTime_ns;
	csEvent * mEventsRoot;
};

