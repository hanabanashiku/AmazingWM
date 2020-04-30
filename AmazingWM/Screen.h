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
		/// <returns>The virtual coordinates of the screen.</returns>
		RECT getCoordinates();

		static LPRECT getCoordinates(HMONITOR monitor);


		/// <summary>Get the clients that belong to the screen.</summary>
		/// <returns>A constant vector of clients.</returns>
		const vector<Client*>& const getClients();

		/// <summary>Check if the given rect is inside the screen rect.</summary>
		/// <returns>True if at least 50% of the total area is inside of the screen space.</returns>
		bool isInsideScreenSpace(LPRECT rect);

		/// <summary>Trigger the screen to update client positions.</summary>
		void renderPositions();

		bool operator=(HMONITOR hMonitor);

	private:
		HMONITOR monitor_;
		RECT rect_;
		ILayout* layout_;
	};
}
