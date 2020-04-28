#pragma once

namespace AmazingWM {
	class MessageHook {
	public:
		MessageHook();
		~MessageHook();

	private:
		HHOOK hook_;
	};
}


