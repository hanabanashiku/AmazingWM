#include "pch.h"
#include "Client.h"

namespace AmazingWM {
	Client::Client(HWND hWnd) {
		received_close_sig_ = false;
		hWnd_ = hWnd;
		setPopup();
		hook();
	}


	Client::~Client() {
		unhook();
		DestroyWindow(hTitlebar_);
		// set the original look of the window
		if (!received_close_sig_)
			setStyle(hWnd_, original_style_);
	}

	HWND Client::getHandle() {
		return hWnd_;
	}

	string Client::getName() {
		LPSTR str = new char[128];
		auto n = GetWindowTextA(hWnd_, str, 128);
		if (n < 0)
			throw exception();
		auto out = string(str);
		free(str);
		return out;
	}

	LPRECT Client::getLocation() {
		LPRECT rect = (RECT*)malloc(sizeof(RECT));
		auto res = GetClientRect(hWnd_, rect);
		return rect;
	}

	BOOL Client::setLocation(LPRECT rect) {
		auto x = rect->left;
		auto y = rect->top;
		auto cx = rect->right - x;
		auto cy = rect->bottom - y;
		return SetWindowPos(hWnd_, 0, x, y, cx, cy, SWP_SHOWWINDOW | SWP_NOOWNERZORDER);
	}

	BOOL Client::focus() {
		return SetForegroundWindow(hWnd_);
	}

	BOOL Client::hide() {
		return SetWindowPos(hWnd_, 0, 0, 0, 0, 0, SW_HIDE);
	}

	BOOL Client::show() {
		return ShowWindow(hWnd_, SW_RESTORE);
	}
	
	// hide the titlebar
	void Client::setPopup() {
		SetLastError(NO_ERROR);
		original_style_ = GetWindowLongA(hWnd_, GWL_STYLE); // save the original style.
		setStyle(hWnd_, WS_POPUP);
	}

	void setStyle(HWND hWnd, LONG style) {
		SetWindowLongPtr(hWnd, GWL_STYLE, style);
		SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowWindow(hWnd, SW_SHOW);
	}

	void Client::hook() {
		LPDWORD proc;
		GetWindowThreadProcessId(hWnd_, proc);
		hook_ = SetWindowsHookEx(WH_CALLWNDPROC, nullptr, nullptr, *proc);
	}

	BOOL Client::unhook() {
		return UnhookWindowsHookEx(hook_);
	}

	HWND renderTitlebar() {
		// TODO
	}

	LRESULT CALLBACK CallWindProc(
		_In_ int nCode,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam) {

		CWPSTRUCT* msg = (CWPSTRUCT*)lParam;
		
		switch (msg->message) {
			// TODO
		default:
			break;
		}

		return CallNextHookEx(nullptr, nCode, wParam, lParam);
	}

}
