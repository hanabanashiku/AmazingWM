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
}

