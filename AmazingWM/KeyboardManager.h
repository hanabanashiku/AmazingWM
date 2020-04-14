#pragma once
#include<Windows.h>
#include<vector>

using namespace std;

namespace AmazingWM {
    class KeyboardManager
    {
    public:
        KeyboardManager();
        ~KeyboardManager();
        static bool isModKeyPressed();
        static void ToggleKey(WORD key, bool isDown);
        static vector<WORD>* getPressedKeys();

    private:
        HHOOK hook_;
        void hook();
        BOOL unhook();
        static bool mod_key_down_;
        static vector<WORD> keys_down_;
    };
}
