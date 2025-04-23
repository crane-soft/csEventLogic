#pragma once
#include <stdio.h>

class csEvent {
public:
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
		mEventTime_ns = 0;
	}

private:
	long mEventTime_ns;
	csEvent* mNextEvent;
};

class csEventList
{
public:
	csEventList() {
		mEventsRoot = 0;
		mCurrentTime_ns = 0;
	}
	void InsertEvent(csEvent* newEvent, int delay) {
		long EventTime = mCurrentTime_ns + delay;
		if (newEvent->EventTime() != 0)
			return; // should not happen

		newEvent->setEventTime(EventTime);
		if (mEventsRoot == 0) {
			mEventsRoot = newEvent;
		} else {
			csEvent* prevEvent = 0;
			csEvent* iEvent;
			for (iEvent = mEventsRoot; iEvent != 0; iEvent = iEvent->NextEvent()) {
				if (EventTime < iEvent->EventTime()) {
					break;
				}
				prevEvent = iEvent;
			}
			if (prevEvent == 0) {
				InsertFront(newEvent);
			} else {
				prevEvent->InsertAfter(newEvent);
			}
		}
	}

	void InsertFront(csEvent* newEvent) {
		csEvent* prevRoot = mEventsRoot;
		mEventsRoot = newEvent;
		mEventsRoot->setNextEvent(prevRoot);
	}

	csEvent* TakeRootEvent() {
		csEvent* fEvent = mEventsRoot;
		if (fEvent != 0) {
			mCurrentTime_ns = fEvent->EventTime();
			printf("EV:%4d ", mCurrentTime_ns);
			mEventsRoot = mEventsRoot->NextEvent();
			fEvent->Clear();
		}
		return fEvent;
	}
private:
	long mCurrentTime_ns;
	csEvent * mEventsRoot;
};

