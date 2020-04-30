#pragma once

namespace AmazingWM {
	[event_source(native)]
	class MessageHook {
	public:
		MessageHook(HINSTANCE hInst);
		~MessageHook();

		/// <summary>Fired when a client is to be shown on the shell.</summary>
		__event void clientCreated(HWND hWnd);

		/// <summary>Fired when a client is to be removed from the shell.</summary>
		__event void clientDestroyed(HWND hWnd);

		/// <summary>Fired when a monitor has been added, removed, or the virtual coordinates have changed.</summary>
		__event void displayChanged();

	private:
		HHOOK hook_;
		HHOOK shell_;
		void hookEvents();
		void unhookEvents();
	};
}


