#pragma once

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	inline ApiChoice StringToApiChoice(const std::string& apiChoice) {
		if (apiChoice == "Directx12") {
			return ApiChoice::eDirectx12;
		}
		if (apiChoice == "Vulkan") {
			return ApiChoice::eVulkan;
		}

		return ApiChoice::eCustom;
	}
}
