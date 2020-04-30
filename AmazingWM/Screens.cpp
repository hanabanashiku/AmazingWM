#include "pch.h"
#include "Screens.h"
#include "Clients.h"

namespace AmazingWM {
	Screens::Screens() {
		screens_ = vector<Screen*>();
		map_ = map<Screen*, vector<Client*>>();
		focused_screen_ = nullptr;
		if (
			EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this))
			!= 0)
			throw exception();
	}


	Screens::~Screens() {
		for (auto s : screens_)
			removeScreen(s);
	}

	const vector<Screen*>& const Screens::getScreens() {
		return screens_;
	}

	Screen * Screens::getScreen(HMONITOR hMonitor) {
		auto screen = find(screens_.begin(), screens_.end(), hMonitor);

		return (screen != screens_.end()) ? *screen : nullptr;
	}

	const Screen * const Screens::getFocusedScreen() {
		return focused_screen_;
	}

	void Screens::setFocusedScreen(Screen * screen) {
		if (!screenExists(screen))
			throw exception();

		focused_screen_ = screen;
	}

	bool Screens::screenExists(Screen * screen) {
		return find(screens_.begin(), screens_.end(), screen) != screens_.end()
			&& map_.find(screen) != map_.end();
	}

	void Screens::addScreen(Screen * screen) {
		if (find(screens_.begin(), screens_.end(), screen) == screens_.end()) {
			screens_.push_back(screen);
		}

		if (map_.find(screen) != map_.end())
			map_[screen] = vector<Client*>();

		if (focused_screen_ == nullptr)
			focused_screen_ = screen;

		// If there were no screens before, add them all to the screen.
		if (screens_.size() == 1) {
			extern Clients* clients;
			for (auto c : clients->getClients) {
				addClientToScreen(c, screen, false);
			}
		}

		screen->renderPositions();
	}

	void Screens::removeScreen(Screen * screen) {
		Screen* replace;

		auto it = find(screens_.begin(), screens_.end(), screen);
		if (it == screens_.end())
			return;
		auto i = distance(screens_.begin(), it);
		
		// choose a screen to move the old clients to
		if (screens_.size() == 0)
			replace = nullptr;
		else if (i == 0) {
			auto j = screens_.size() - 1;
			replace = screens_[j];
		}
		else
			replace = screens_[i - 1];

		if (focused_screen_ == screen)
			focused_screen_ = replace;

		screens_.erase(screens_.begin() + i);

		auto clients = getClients(screen);

		if(replace != nullptr)
			for (auto &client : clients) {
				moveClient(client, replace);
			}

		map_.erase(screen);

		delete screen;
	}

	const vector<Client*>& const Screens::getClients(Screen * screen) {
		return map_[screen];
	}
	void Screens::addClientToScreen(Client * client, Screen * target, bool render = true) {
		auto vec = &map_[target];
		vec->push_back(client);
		client->assignScreen(target);

		if(render)
			target->renderPositions();
	}

	void Screens::removeClientFromScreen(Client * client) {
		auto target = client->getScreen();
		
		if (target == nullptr)
			return;

		client->assignScreen(nullptr);
		auto vec = &map_[target];
		vec->erase(remove(vec->begin(), vec->end(), client));
		target->renderPositions();
	}

	void Screens::moveClient(Client * client, Screen * target) {
		auto screen = client->getScreen();
		
		if (screen == target)
			return;
		if (!screenExists(target))
			throw exception();

		removeClientFromScreen(client);
		addClientToScreen(client, target);
	}

	void Screens::displayChanged() {
		vector<Screen*>* discovered_screens = new vector<Screen*>();

		// Enumerate all of the screens to look for changes
		EnumDisplayMonitors(NULL, NULL, MonitorChangedEnumProc, reinterpret_cast<LPARAM>(discovered_screens));

		// look for screens to remove
		for (auto screen : screens_) {
			if (find(discovered_screens->begin(), discovered_screens->end(), screen) == discovered_screens->end()) {
				removeScreen(screen);
			}
		}

		delete discovered_screens;
	}

	// Used to find monitors one by one.
	BOOL MonitorEnumProc(
		HMONITOR hMonitor,
		HDC hdc,
		LPRECT lpRect,
		LPARAM lParam) {
		extern int* current_tag;
		auto screens = reinterpret_cast<Screens*>(lParam);
		Screen* screen = new Screen(hMonitor, *lpRect);
		screens->addScreen(screen);
		return TRUE; // continue enumerating
	}

	// Used to find monitors to add or update.
	BOOL MonitorChangedEnumProc(
		HMONITOR hMonitor,
		HDC hdc,
		LPRECT lpRect,
		LPARAM lParam) {
		
		extern Screens* screens;
		vector<Screen*>* discovered_screens = reinterpret_cast<vector<Screen*>*>(lParam);

		auto screen = screens->getScreen(hMonitor);
		auto rect = *Screen::getCoordinates(hMonitor);

		// it's a new screen, add it.
		if (screen == nullptr) {
			screen = new Screen(hMonitor, rect);
			screens->addScreen(screen);
		}
		// maybe the size changed?
		else if(!rectEquals(&rect, &screen->getCoordinates())) {
			screen->sizeChangedEvent(rect);
		}

		discovered_screens->push_back(screen);
	}

	static bool rectEquals(LPRECT a, LPRECT b) {
		return a->top == b->top &&
			a->right == b->right &&
			a->bottom == b->bottom &&
			a->left == b->left;
	}
}

