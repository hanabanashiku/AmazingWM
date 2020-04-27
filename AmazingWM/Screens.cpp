#include "pch.h"
#include "Screens.h"

namespace AmazingWM {
	Screens::Screens() {
		screens_ = vector<Screen*>();
		map_ = map<Screen*, vector<Client*>>();
		if (
			EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this))
			!= 0)
			throw exception();
	}


	Screens::~Screens() {
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
	}

	void Screens::removeScreen(Screen * screen) {
		Screen* replace;

		auto it = find(screens_.begin(), screens_.end(), screen);
		if (it == screens_.end())
			return;
		auto i = distance(screens_.begin(), it);
		int j;
		if (i == 0)
			j = screens_.size() - 1;
		else
			j = i - 1;
		replace = screens_[j];

		screens_.erase(screens_.begin() + i);

		auto clients = getClients(screen);

		for (auto &client : clients) {
			moveClient(client, replace);
		}

		map_.erase(screen);
	}

	const vector<Client*>& const Screens::getClients(Screen * screen) {
		return map_[screen];
	}
	void Screens::addClientToScreen(Client * client, Screen * target) {
		auto vec = &map_[target];
		vec->push_back(client);
		client->assignScreen(target);
		target->renderPositions();
	}

	void Screens::removeClientFromScreen(Client * client, Screen * target) {
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

		removeClientFromScreen(client, screen);
		addClientToScreen(client, target);
	}

	BOOL MonitorEnumProc(
		HMONITOR hMonitor,
		HDC hdc,
		LPRECT lpRect,
		LPARAM lParam) {
		extern int* current_tag;
		auto screens = reinterpret_cast<Screens*>(lParam);
		auto screen = Screen(hMonitor, *lpRect);
	}
}

