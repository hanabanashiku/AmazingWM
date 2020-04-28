#pragma once
#include "Client.h"

namespace AmazingWM {

	/// <summary> A layout used to render screen positions.</summary>
	class ILayout {
	public:
		virtual ~ILayout();
		virtual void render(Client** clients, size_t size, RECT* bounds);
	};
}