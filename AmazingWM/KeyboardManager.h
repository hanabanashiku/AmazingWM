#pragma once
#include<Windows.h>
#include<vector>

using namespace std;

namespace AmazingWM {
	/// <summary>The object responsible for managing keyboard input.</summary>
    class KeyboardManager  {
    public:
        KeyboardManager();
        ~KeyboardManager();

		/// <summary>Check if the mod key is pressed.</summary>
		/// <returns>True if the mod key is pressed down.</returns>
        static bool isModKeyPressed();

		/// <summary> Note the status of a key that has changed.</summary>
		/// <params name="key">The virtual key that was changed.</params>
		/// <params name="bool">True if it is pressed down.</params>
        static void ToggleKey(WORD key, bool isDown);

		/// <summary>Check the keys that are currently pressed.</summary>
		/// <returns>A vector containing the keys that are currently pressed alongside the mod key.</returns>
        static const vector<WORD>& const getPressedKeys();

    private:
        HHOOK hook_;
        void hook();
        BOOL unhook();
        static bool mod_key_down_;
        static vector<WORD> keys_down_;
    };
}
