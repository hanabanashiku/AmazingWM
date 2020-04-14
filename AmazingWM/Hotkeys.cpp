#include "pch.h"
#include "Hotkeys.h"
#include<algorithm>

using namespace std;

namespace AmazingWM {
    Hotkeys::Hotkeys() {
        keybinds_ = map<Keybinds, vector<WORD>>();
    }


    Hotkeys::~Hotkeys() { }

    WORD Hotkeys::getModKey() {
        return mod_key_;
    }

    void Hotkeys::setModKey(WORD key) {
        if (key != VK_MENU && key != VK_CONTROL &&
            key != VK_SHIFT
            && key != VK_LWIN && key != VK_RWIN)
            throw "Invalid mod key.";
        mod_key_ = key;
    }

    void Hotkeys::setKeybind(Keybinds keybind, vector<WORD> keys)
    {
        if (keybind == Keybinds::Null)
            throw "Unexpected keybind 'Null'";

        sort(keys.begin(), keys.end());
        keybinds_[keybind] = keys;
    }

    vector<WORD> Hotkeys::getKeybind(Keybinds keybind)
    {
        if (keybind == Keybinds::Null)
            throw "Unexpected keybind 'Null'";

        return keybinds_[keybind];
    }

// check if the key combination pressed represents a keybind
    Keybinds Hotkeys::existsAsKeybind(vector<WORD> keys)
    {
        sort(keys.begin(), keys.end());
        for (auto it = keybinds_.begin(); it != keybinds_.end(); ++it) {
            if (it->second == keys)
                return it->first;
        }
        return Keybinds::Null;
    }

    void Hotkeys::setDefaults() {
        setModKey(VK_LWIN);
        // todo
    }
}

