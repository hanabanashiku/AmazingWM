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
		renderPositions();
	}

	HMONITOR Screen::getHandle() {
		return monitor_;
	}

	RECT Screen::getCoordinates() {
		return  rect_;
	}

	LPRECT Screen::getCoordinates(HMONITOR monitor) {
		if (monitor == nullptr)
			return nullptr;

		auto info = new MONITORINFO();
		info->cbSize = sizeof(MONITORINFO);

		GetMonitorInfo(monitor, info);

		auto size = info->rcMonitor;
		delete info;
		return &size;
	}

	const vector<Client*>& const Screen::getClients() {
		return screens->getClients(this);
	}

	bool Screen::isInsideScreenSpace(LPRECT lprc) {
		auto monitor = MonitorFromRect(lprc, MONITOR_DEFAULTTONEAREST);
		
		return monitor_ == monitor;
	}

	void Screen::renderPositions() {
		extern int current_tag;
		RECT* bounds = &getCoordinates();
		list<Client*> l = list<Client*>();

		for (auto c : getClients()) {
			if (c->isTagged(current_tag) && c->isVisible())
				l.push_front(c);
		}
		
		auto clients = new Client*[l.size()];
		copy(l.begin(), l.end(), clients);
		layout_->render(clients, l.size(), bounds);
	}

	bool Screen::operator=(HMONITOR hMonitor) {
		return hMonitor == getHandle();
	}
}

