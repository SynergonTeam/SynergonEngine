#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include <cstdint>

namespace Synergon::Rhi {
	struct ShaderInputPoolDescriptor {
		ShaderInputType type;
		uint32_t        count;
	};
}  //  namespace Synergon::Rhi
