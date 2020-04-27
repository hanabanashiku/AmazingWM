#pragma once
#include<Windows.h>
#include<map>
#include<vector>
#include<list>
#include "Screen.h"
#include "Client.h"

using namespace std;

namespace AmazingWM {
	/// <summary>A collection of screens discovered by the window manager.</summary>
	class Screens {
	public:
		Screens();
		~Screens();

		/// <summary>Get all screens currently discovered by the window manager.</summary>
		/// <returns>A constant vector of screen pointers.</returns>
		const vector<Screen*>& const getScreens();

		/// <summary>Get the screen that currently has focus.</summary>
		/// <returns>A pointer to the screen that has focus.</returns>
		const Screen* const getFocusedScreen();

		/// <summary>Change the screen that currently has focus.</summary>
		/// <param name="screen">The screen to set to be focused.</param>
		void setFocusedScreen(Screen* screen);

		/// <summary>Checks that the pointer is still valid.</summary>
		/// <params name="screen">A pointer to a screen.</param>
		/// <returns>True if the screen still exists.</returns>
		bool screenExists(Screen* screen);

		/// <summary>Adds a new screen to the manager.</summary>
		/// <params name="screen">A pointer to the screen to add.</params>
		void addScreen(Screen* screen);

		/// <summary>Removes a screen from the manager.</summary>
		/// <params name="screen">A pointer to the screen to remove.</params>
		void removeScreen(Screen* screen);

		/// <summary>Get the clients that belong to a screen.</summary>
		/// <params name="screen">A pointer to the screen.</params>
		/// <returns>A constant vector of clients.</returns>
		const vector<Client*>& const getClients(Screen* screen);

		/// <summary>Adds a client to a screen</summary>
		/// <params name="client">The client to add.</params>
		/// <params name="target">The new screen.</params>
		void addClientToScreen(Client* client, Screen* target);

		/// <summary>Remove a client from a screen</summary>
		/// <params name="client">The client to remove.</params>
		/// <params name="target">The screen.</params>
		void removeClientFromScreen(Client* client, Screen* target);

		/// <summary>Move a client to a new screen.</summary>
		/// <params name="client">The client to move.</params>
		/// <params name="target">The new screen.</params>
		void moveClient(Client* client, Screen* target);

	private:
		map<Screen*, vector<Client*>> map_;
		vector<Screen*> screens_;
		Screen* focused_screen_;
	};
}

