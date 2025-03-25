#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include <cstdint>

namespace Synergon::Rhi {
	struct BufferDescriptor {
		MemoryUsage       memoryUsage;
		BufferUsage::Type usage;
		uint64_t          size;
	};
}  // namespace Synergon::Rhi
