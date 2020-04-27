#pragma once
#include "ILayout.h"

namespace AmazingWM {
	/// <summary>A display screen.</summary>
	class Screen {
	public:
		/// <params name="monitor">A pointer to the monitor.</params>
		/// <params name="rect">The virtual coordinates of the screen.</params>
		Screen(HMONITOR monitor, RECT rect);
		~Screen();

		void sizeChangedEvent(RECT rect);

		/// <summary> Get the handle of the display monitor.</summary>
		/// <returns> A pointer to the handle.</returns>
		HMONITOR getHandle();

		/// <summary> Get the location of the screen.</summary>
		/// <returns>The virtual coordinates of the screen.</summary>
		RECT getCoordinates();

		/// <summary>Get the clients that belong to the screen.</summary>
		/// <returns>A constant vector of clients.</returns>
		const vector<Client*>& const getClients();

		/// <summary>Trigger the screen to update client positions.</summary>
		void renderPositions();

		/// <summary>Set the screen as the current focused screen.</summary>
		void focus();

	private:
		HMONITOR monitor_;
		RECT rect_;
		ILayout* layout_;
	};
}
