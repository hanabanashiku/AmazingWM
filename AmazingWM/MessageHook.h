#pragma once

namespace AmazingWM {
	[event_source(native)]
	class MessageHook {
	public:
		MessageHook(HINSTANCE hInst);
		~MessageHook();
		__event BOOL clientCreated(HWND hWnd);

	private:
		HHOOK hook_;
		HHOOK shell_;
		void hookEvents();
		void unhookEvents();
	};
}


