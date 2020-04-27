#include "pch.h"
#include <iostream>
#include<cstdlib>
#include "KeyboardManager.h"
#include "Settings.h"
#include "Hotkeys.h"
#include "Screens.h"

using namespace std;

namespace AmazingWM {
    KeyboardManager* keyboardManager;
    Settings* settings;
    Hotkeys* hotkeys;
	Screens* screens;
	int current_tag;

    int main() {
		current_tag = 1;
        keyboardManager = &KeyboardManager();
		settings = &Settings();
		hotkeys = settings->getHotkeys();
		screens = &Screens(&current_tag);

		atexit(lam);
    }

    // Runs on exit
    void lam() {

    }
}

