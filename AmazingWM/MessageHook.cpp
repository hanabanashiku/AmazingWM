#include "pch.h"
#include "MessageHook.h"

using namespace std;

namespace AmazingWM {
	MessageHook::MessageHook() {
		hook_ = SetWindowsHookExA(WH_CALLWNDPROC, CallWndProc, NULL, 0);
	}


	MessageHook::~MessageHook() {
		UnhookWindowsHookEx(hook_);
	}

	LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) {
		// todo
	}
}


