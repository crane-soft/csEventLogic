#pragma once
#include <initializer_list>
#include <string>
#include <iostream>

class csLink {
public:
	csLink() {
		mNextLink = 0;
		mLinkName = "";
	}

	void setName(std::string name) { mLinkName = name; }
	std::string Name() { return mLinkName; }

	void addLink(csLink* newLink) {
		if (mNextLink == 0) {
			mNextLink = newLink;
		} else {
			// newLink may have already some links
			newLink->append(mNextLink);
			mNextLink = newLink;
		}
	}
		
	void addLinks(std::initializer_list<csLink*> list) {
		for (csLink* elem : list) {
			addLink(elem);
		}
	}

	void append(csLink* nLink) {
		if (mNextLink == 0) {
			mNextLink = nLink;
		} else {
			csLink* iLink = mNextLink;

			while (iLink->mNextLink != 0) {
				iLink = iLink->mNextLink;
			}
			iLink->mNextLink = nLink;
		}
	}

	void printNet(std::string rootNode = "") {

		std::cout << rootNode << "->" << mLinkName;
		if (mNextLink != 0) {
			mNextLink->printNet();
		} else {
			std::cout << "\r\n";
		}
	}
	csLink* NextLink() { return mNextLink; }

protected:
	csLink* mNextLink;
	std::string mLinkName;
};
