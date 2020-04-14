#include "pch.h"
#include <iostream>
#include<cstdlib>
#include "KeyboardManager.h"
#include "Settings.h"
#include "Hotkeys.h"

using namespace std;

namespace AmazingWM {
    KeyboardManager* keyboardManager;
    Settings* settings;
    Hotkeys* hotkeys;

    int main() {
        keyboardManager = &KeyboardManager();
        hotkeys = &Hotkeys();

		atexit(lam);
    }

    // Runs on exit
    void lam() {

    }
}

