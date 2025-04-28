#pragma once
#include <initializer_list>
#include <string>
class csLink {
public:
	csLink() {
		mNextLink = 0;
	}

	void setName(std::string name) { LinkName = name; }

	void addLink(csLink* newLink) {
		if (mNextLink == 0) {
			mNextLink = newLink;
		} else {
			// newLink may hav already some links
			newLink->appendLink(mNextLink);
			mNextLink = newLink;
		}
	}
		
	void addLinks(std::initializer_list<csLink*> list) {
		for (csLink* elem : list) {
			addLink(elem);
		}
	}

	csLink* NextLink() { return mNextLink; }

protected:
	csLink* mNextLink;
	std::string LinkName;

private:
	void appendLink(csLink *nLink) {
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
};
