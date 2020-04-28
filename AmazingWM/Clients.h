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

		/// <summary>Add a new client to the window manager.</summary>
		/// <params name="client">The client to add.</params>
		void addClient(Client* client);

		/// <summary>Remove a client from the window manager and delete the reference.</summary>
		/// <params name="client">The client to remove.</params>
		void removeClient(Client* client);

		/// <summary>Check if a client has been added to the window manager.</summary>
		/// <params name="client">The client to check.</params>
		/// <returns>True if the client has been added.</returns>
		bool exists(Client* client);

		/// <summary>Set a client to have focus.</summary>
		/// <params name="client">The client to focus.</params>
		/// <returns>A non-zero value on success.</returns>
		BOOL focusClient(Client* client);

		/// <summary>Get the client that currently has focus.</summary>
		/// <returns>A pointer to the focused client.</returns>
		Client* const getFocusedClient();

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
		Client* focused_client_;
	};
}


