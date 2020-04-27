#pragma once
#include<map>
#include "Client.h"

using namespace std;

namespace AmazingWM {

	/// <summary>A collection of clients that have been recognized by the window manager.</summary>
	class Clients {
	public:
		Clients();
		~Clients();
		/// <summary>Gets all clients that have been discoverd.</summary>
		/// <returns>A reference to all clients</summary>
		const vector<Client*>& const getClients();

		/// <summary>Assign a tag to a client.</summary>
		/// <param name="client">The client to tag.</param>
		/// <param name="tag">The tag, 1-9, to mark on the client</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		void assignTag(Client* client, int tag);
		
		/// <summary>Remove a tag from the client.</summary>
		/// <param name="client">The client with the tag.</param>
		/// <param name="tag">The tag, 1-9, to remove.</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		void removeTag(Client* client, int tag);

		/// <summary>Tag a client with the tag, or remove it if it is already set.</summary>
		/// <param name="client">The client whose tag to toggle.</param>
		/// <param name="tag">The tag to toggle</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		bool toggleTag(Client* client, int tag);

		/// <summary>Change the tag to display on screen.</summary>
		/// <param name="tag">The tag to display</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		void setCurrentTag(int tag);

	private:
		vector<Client*> clients_;
		map<int, vector<Client*>> client_tags_;
	};
}


