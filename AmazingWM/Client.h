#include<Windows.h>
#include<string>

using namespace std;

namespace AmazingWM {
	class Client
	{
	public:
		Client(HWND hWnd);
		~Client();
		HWND getHandle();
		string getName();
		LPRECT getLocation();
		BOOL setLocation(LPRECT rect);
		BOOL focus();
		BOOL hide();
		BOOL show();
		

	private:
		HWND hWnd_;
		HWND hTitlebar_;
		HHOOK hook_;
		bool received_close_sig_;
		LONG original_style_;
		void setPopup();
		HWND renderTitlebar();
		void hook();
		BOOL unhook();
	};
}
#pragma once


