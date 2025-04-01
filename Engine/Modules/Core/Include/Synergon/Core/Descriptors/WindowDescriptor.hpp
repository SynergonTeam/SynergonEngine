#pragma once

#include <cstdint>
#include <string>

namespace Synergon::Core {

	struct WindowDescriptor {
		uint32_t    width      = 0;
		uint32_t    height     = 0;
		std::string title      = "";
		std::string iconPath   = "";
		bool        resizable  = true;
		bool        fullscreen = false;
	};
}  // namespace Synergon::Core
