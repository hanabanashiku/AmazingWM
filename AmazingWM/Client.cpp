#include "pch.h"
#include "Client.h"

namespace AmazingWM {
	Client::Client(HWND hWnd) {
		received_close_sig_ = false;
		hWnd_ = hWnd;
		tags_ = vector<int>();
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
		delete[] str;
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
		
		auto flags = SWP_NOOWNERZORDER;
		if (isVisible) flags |= SWP_SHOWWINDOW;
		return SetWindowPos(hWnd_, 0, x, y, cx, cy, flags);
	}

	void Client::assignScreen(Screen * screen) {
		pScreen_ = screen;
	}

	Screen * const Client::getScreen() {
		return pScreen_;
	}

	bool Client::isTagged(int tag) {
		return !tags_.empty() && find(tags_.begin(), tags_.end(), tag) != tags_.end();
	}

	void Client::assignTag(int tag) {
		if (!validateTag(tag))
			throw exception();

		if (isTagged(tag))
			return;
		tags_.push_back(tag);
		sort(tags_.begin(), tags_.end());
		setVisibilityByTag();
	}

	void Client::removeTag(int tag) {
		if (!validateTag(tag))
			throw exception();

		if (!isTagged(tag))
			return;

		tags_.erase(remove(tags_.begin(), tags_.end(), tag), tags_.end());
		setVisibilityByTag();
	}

	const vector<int>& Client::getTags() const {
		return tags_;
	}

	BOOL Client::hide(bool render = true) {
		auto result = SetWindowPos(hWnd_, 0, 0, 0, 0, 0, SW_HIDE);

		if (result != 0 && render)
			pScreen_->renderPositions();
		return result;
	}

	BOOL Client::show(bool render = true) {
		auto result = ShowWindow(hWnd_, SW_RESTORE);
		
		if (result != 0 && render)
			pScreen_->renderPositions();
		return result;
	}

	bool Client::isVisible() {
		return IsWindowVisible(hWnd_) != 0;
	}
	
	void Client::setVisibilityByTag(bool render = true) {
		extern int* current_tag;
		
		bool should_display_window = isTagged(*current_tag);
		bool is_displayed = isVisible();

		if (should_display_window == is_displayed)
			return;
		else if (should_display_window)
			show(render);
		else
			hide(render);
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

	bool Client::validateTag(const int tag) {
		if (tag < 1 || tag > 9)
			return false;
		return true;
	}

	bool Client::operator==(const HWND hWnd) {
		return hWnd_ == hWnd;
	}

}
