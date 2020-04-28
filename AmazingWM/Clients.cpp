#include "pch.h"
#include "Clients.h"
#include "Screens.h"

namespace AmazingWM {
	Clients::Clients() {
		clients_ = vector<Client*>();

		// set up client tag vectors
		client_tags_ = map<int, vector<Client*>>();
		for (auto i = 1; i <= 9; ++i)
			client_tags_[i] = vector<Client*>();

		// Pull the current windows
		EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(this));
	}


	Clients::~Clients() {
		for (auto c : clients_)
			removeClient(c);
	}

	const vector<Client*>& const AmazingWM::Clients::getClients() {
		return clients_;
	}

	void Clients::addClient(Client * client) {
		if (client == nullptr)
			return;

		if (exists(client))
			return;

		clients_.push_back(client);
		extern Screens* screens;

		for (auto s : screens->getScreens()) {
			if (s->isInsideScreenSpace(client->getLocation())) {
				client->assignScreen(s);
				break;
			}
		}

		assert(client->getScreen() != nullptr);

		// todo make this a setting.
		focusClient(client);
	}

	void Clients::removeClient(Client * client) {
		if (client == nullptr || !exists(client))
			return;

		for (auto tag : client->getTags())
			removeTag(client, tag);

		extern Screens* screens;
		screens->removeClientFromScreen(client);

		delete client;
	}

	bool Clients::exists(Client * client) {
		return find(clients_.begin(), clients_.end(), client) != clients_.end();
	}

	BOOL Clients::focusClient(Client * client) {
		if (client == nullptr || focused_client_ == client)
			return;

		extern Screens* screens;
		auto screen = client->getScreen();
		if (screens->getFocusedScreen() != screen)
			screens->setFocusedScreen(screen);

		focused_client_ = client;
		SetForegroundWindow(client->getHandle());
	}

	Client * const Clients::getFocusedClient() {
		return focused_client_;
	}

	void Clients::assignTag(Client * client, int tag) {
		if (client->isTagged(tag))
			return;
		client->assignTag(tag);
		client_tags_[tag].push_back(client);
	}

	void Clients::removeTag(Client * client, int tag) {
		if (!client->isTagged(tag))
			return;
		client->removeTag(tag);
		
		auto vec = client_tags_[tag];
		vec.erase(remove(vec.begin(), vec.end(), client));
	}
	bool Clients::toggleTag(Client * client, int tag) {
		if (client->isTagged(tag)) {
			removeTag(client, tag);
			return false;
		}
		else {
			assignTag(client, tag);
			return true;
		}
	}

	void Clients::setCurrentTag(int tag) {
		if (!Client::validateTag(tag))
			throw exception();

		extern int current_tag;
		extern Screens* screens;
		
		if (current_tag == tag)
			return;

		current_tag = tag;

		for (auto client : clients_) {
			client->setVisibilityByTag(false);
		}

		for (auto screen : screens->getScreens()) {
			screen->renderPositions();
		}
	}

	// cycle through all the current clients.
	BOOL CALLBACK EnumWindowsProc(
		_In_ HWND hWnd,
		_In_ LPARAM lParam) {
		auto clients = reinterpret_cast<Clients*>(lParam);

		// todo ensure the startmenu / amazingwm taskbar isn't coming up here.

		Client * c = new Client(hWnd);
		clients->addClient(c);
		return TRUE; // keep enumerating
	}
}


