#include "pch.h"
#include <iostream>
#include<cstdlib>
#include "KeyboardManager.h"
#include "Settings.h"
#include "Hotkeys.h"
#include "Screens.h"
#include "Clients.h"
#include "MessageHook.h"

using namespace std;

namespace AmazingWM {
    KeyboardManager* keyboardManager;
    Settings* settings;
    Hotkeys* hotkeys;
	Screens* screens;
	Clients* clients;
	int current_tag;

	MessageHook* messageHook;

    int WINAPI wWinMain(HINSTANCE instance, HINSTANCE hPrevInstance,
		PWSTR pCmdLine, int nCmdShow) {
		current_tag = 1;
        keyboardManager = new KeyboardManager();
		settings = new Settings();
		hotkeys = settings->getHotkeys();
		screens = new Screens();
		clients = new Clients();
		messageHook = new MessageHook();

		atexit(lam);
    }

    // Runs on exit
    void lam() {
		delete keyboardManager;
		delete settings;
		delete hotkeys;
		delete screens;
		delete clients;
		delete messageHook;
    }
}

