#pragma once
#include<Windows.h>
#include<string>
#include "Screen.h"

using namespace std;

namespace AmazingWM {
	/// <summary>A client top-level window that is instantiated in the Windows environment.</summary>
	class Client {
	public:
		/// <param name="hWnd">A pointer to a window handle.</param>
		Client(HWND hWnd);
		~Client();

		/// <summary>Get the win32 window handle.</summary>
		/// <returns>A pointer to the handle.</returns>
		HWND getHandle();
		
		/// <summary>Get the title of the client.</summary>
		/// <returns>A string containing the title, with a maximum size of 128 characters.</returns>
		string getName();

		/// <summary>Get the location of the window on screen. </summary>
		/// <returns> A pointer to a RECT object that refers to coordinates on the virtual screen.</returns>
		LPRECT getLocation();

		/// <summary>Move the window to a new virtual coordinate.</summary>
		/// <params name="rect">A pointer to a RECT containing the new coordinates.</summary>
		/// <returns>0 on success, non-zero on failure.</returns>
		BOOL setLocation(LPRECT rect);

		/// <summary>Set the screen that should be responsible for the window.</summary>
		/// <param name="screen"> A pointer to the screen.</param>
		void assignScreen(Screen* screen);

		/// <summary>Get the screen that is responsible for managing the client.</summary>
		/// <returns>A pointer to the screen.</returns>
		Screen* const getScreen();

		/// <summary>Determines if the client has a tag.</summary>
		/// <param name="tag">The tag to look for.</parma>
		/// <returns>True if the client has the given tag.</returns>
		bool isTagged(int tag);

		/// <summary>Mark the client with the given tag.</summary>
		/// <param name="tag">The tag to assign.</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		void assignTag(int tag);

		/// <summary>Remove the given tag from the client.</summary>
		/// <param name="tag">The tag to remove.</param>
		/// <exception cref="exception">If an invalid tag is given.</exception>
		void removeTag(int tag);

		/// <summary>Get all tags assigned to the client.</summary>
		/// <returns>A constant vector of tags.</returns>
		const vector<int>& getTags() const;


		/// <summary>Hide (minimize) the current client.</summary>
		/// <param name="render">Whether to tell the screen to render the change to the window.</param>
		/// <returns>0 on success, a non-zero value on failure.</returns>
		BOOL hide(bool render = true);

		/// <summary>Restore the current client.</summary>
		/// <param name="render">Whether to tell the screen to render the change to the window.</param>
		/// <returns>0 on success, a non-zero value on failure.</returns>
		BOOL show(bool render = true);

		/// <summary>Determine if the client is visible in screen space. </summary>
		/// <returns>True if the client is on the screen.</returns>
		bool isVisible();

		/// <summary>Set the client to be visible if one of its tags is currently set as the current tag.</summary>
		/// <param name="render">Whether to tell the screen to render the change to the window.</param>
		void setVisibilityByTag(bool render = true);

		// Helper function for validating a tag parameter's value.
		static bool validateTag(const int tag);

	private:
		HWND hWnd_;
		HWND hTitlebar_;
		HHOOK hook_;
		Screen* pScreen_;
		vector<int> tags_;
		bool received_close_sig_;
		LONG original_style_;
		void setPopup();
		HWND renderTitlebar();
		void hook();
		BOOL unhook();
	};
}
