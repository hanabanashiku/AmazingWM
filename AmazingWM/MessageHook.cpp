#include "pch.h"
#include "MessageHook.h"
#include "Clients.h"

using namespace std;

namespace AmazingWM {
	MessageHook::MessageHook(HINSTANCE hInst) {
		hook_ = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, hInst, 0);
		shell_ = SetWindowsHookEx(WH_SHELL, ShellProc, hInst, 0);
		hookEvents();
	}


	MessageHook::~MessageHook() {
		UnhookWindowsHookEx(hook_);
		unhookEvents();
	}

	void MessageHook::hookEvents() {
		extern Clients* clients;

		__hook(clients->clientCreated, this, clientCreated);
	}

	void MessageHook::unhookEvents() {
		extern Clients* clients;

		__unhook(clients->clientCreated, this, clientCreated);
	}

	LRESULT CALLBACK CallWndProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		if (wParam != 0) // this message was sent by our thread.
			return CallNextHookEx(NULL, nCode, wParam, lParam);

		extern MessageHook* messageHook;
		auto msg = (CWPSTRUCT*)lParam;

		switch (msg->message) {
		case WM_MOVE:
			break;
		case WM_SIZE:
			break;
		case WM_ACTIVATE:
			break;
		case WM_DISPLAYCHANGE:
			break;
		}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	LRESULT CALLBACK ShellProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		extern MessageHook* messageHook;

		switch (nCode) {
		case HSHELL_WINDOWCREATED:
			auto hWnd = (HWND)wParam;
			__raise messageHook->clientCreated(hWnd);
			break;
		case HSHELL_WINDOWDESTROYED:
			break;
		}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
}


