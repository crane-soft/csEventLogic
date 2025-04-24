#pragma once
#include <initializer_list>
class csLink {
public:
	csLink() {
		mNextLink = 0;
		mLastLink = this;
	}


	void addLink(csLink* newLink) {
		mLastLink->setLink(newLink);
		mLastLink = newLink;
	}
		
	void addLinks(std::initializer_list<csLink*> list) {
		for (csLink* elem : list) {
			addLink(elem);
		}
	}

	csLink* NextLink() { return mNextLink; }
	csLink* LastLink() { return mLastLink; }

protected:
	csLink* mNextLink;
	csLink* mLastLink;
private:
	void setLink(csLink* newLink) {
		mNextLink = newLink;
		mLastLink = newLink->LastLink();
	}

};

