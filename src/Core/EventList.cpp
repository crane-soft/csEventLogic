#include "EventList.h"

csEventList::csEventList() {
	mEventsRoot = 0;
	mCurrentTime_ns = 0;
}
void csEventList::InsertEvent(csEvent* newEvent, int delay) {
	long EventTime = mCurrentTime_ns + delay;
	if (newEvent->Pending()) {
		if (EventTime == newEvent->EventTime())
			return;
		RemoveEvent(newEvent);
	}

	newEvent->setEventTime(EventTime);
	newEvent->setPending();
	if (mEventsRoot == 0) {
		mEventsRoot = newEvent;
	} else {
		csEvent* prevEvent = 0;
		for (csEvent* iEvent = mEventsRoot; iEvent != 0; iEvent = iEvent->NextEvent()) {
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

void csEventList::RemoveEvent(csEvent* Event) {
	csEvent* prevEvent = 0;

	for (csEvent* iEvent = mEventsRoot; iEvent != 0; iEvent = iEvent->NextEvent()) {
		if (iEvent == Event) {
			break;
		}
		prevEvent = iEvent;

	}
	if (prevEvent == 0) {
		mEventsRoot = mEventsRoot->NextEvent();
	} else {
		prevEvent->setNextEvent(Event->NextEvent());
	}

	Event->Clear();

}

void csEventList::InsertFront(csEvent* newEvent) {
	csEvent* prevRoot = mEventsRoot;
	mEventsRoot = newEvent;
	mEventsRoot->setNextEvent(prevRoot);
}

csEvent* csEventList::TakeRootEvent() {
	csEvent* fEvent = mEventsRoot;
	if (fEvent != 0) {
		mCurrentTime_ns = fEvent->EventTime();
		mEventsRoot = mEventsRoot->NextEvent();
		fEvent->Clear();
	}
	return fEvent;
}
