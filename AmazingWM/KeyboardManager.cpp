#include "pch.h"
#include "KeyboardManager.h"
#include "Settings.h"

namespace AmazingWM {

    extern Hotkeys* hotkeys;

    KeyboardManager::KeyboardManager() {
        keys_down_ = vector<WORD>();
        hook();
    }


    KeyboardManager::~KeyboardManager() {
        unhook();
    }

    bool KeyboardManager::isModKeyPressed()
    {
        return mod_key_down_;
    }

    void KeyboardManager::ToggleKey(WORD key, bool isDown)
    {
        auto modKey = hotkeys->getModKey();

        if (key == modKey) {
            mod_key_down_ = isDown;
            return;
        }

        BOOL containsKey = count(keys_down_.begin(), keys_down_.end(), key);

        if (containsKey && isDown)
            return;
        if (!containsKey && !isDown)
            return;

        if (isDown) {
            keys_down_.push_back(key);
            sort(keys_down_.begin(), keys_down_.end());
        }
        else {
            auto it = find(keys_down_.begin(), keys_down_.end(), key);
            if (it != keys_down_.end())
                keys_down_.erase(it);
        }
    }

    const vector<WORD>& const KeyboardManager::getPressedKeys() {
        return keys_down_;
    }

    BOOL KeyboardManager::unhook()
    {
        return UnhookWindowsHookEx(hook_);
    }

    LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
    {
        bool pressed = lParam >> KF_UP == 0;
        UINT modKey = hotkeys->getModKey();

        // Don't grab keys if we aren't using the modkey
        if (!KeyboardManager::isModKeyPressed() && wParam != modKey) {
            return CallNextHookEx(NULL, code, wParam, lParam);
        }

        KeyboardManager::ToggleKey(wParam, pressed);

        Keybinds cmd = hotkeys->existsAsKeybind(KeyboardManager::getPressedKeys());

        if (cmd != Keybinds::Null) {
            // todo Execute operation here
        }

        return CallNextHookEx(NULL, code, wParam, lParam);
    }

    void KeyboardManager::hook() {
        hook_ = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, 0, 0);
    }
}

