#include "pch.h"
#include "Clients.h"
#include "Screens.h"

namespace AmazingWM {
	Clients::Clients() {
		clients_ = vector<Client*>();
		client_tags_ = map<int, vector<Client*>>();
		for (auto i = 1; i <= 9; ++i)
			client_tags_[i] = vector<Client*>();
	}


	Clients::~Clients() {
	}

	const vector<Client*>& const AmazingWM::Clients::getClients() {
		return clients_;
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
}


