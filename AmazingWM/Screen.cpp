#include "pch.h"
#include "Screens.h"

namespace AmazingWM {
	extern Screens* screens;

	Screen::Screen(HMONITOR monitor, RECT rect) {
		monitor_ = monitor;
		rect_ = rect;
	}


	Screen::~Screen() {
	}

	void Screen::sizeChangedEvent(RECT rect) {
		rect_ = rect;
	}

	HMONITOR Screen::getHandle() {
		return monitor_;
	}

	RECT Screen::getCoordinates() {
		return  rect_;
	}

	const vector<Client*>& const Screen::getClients() {
		return screens->getClients(this);
	}

	void Screen::renderPositions() {
		extern int current_tag;
		RECT* bounds = &getCoordinates();
		list<Client*> l = list<Client*>();

		for (auto c : getClients()) {
			if (c->isTagged(current_tag))
				l.push_front(c);
		}
		
		auto clients = new Client*[l.size()];
		copy(l.begin(), l.end(), clients);
		layout_->render(clients, l.size(), bounds);
	}
}

