#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include "Synergon/Rhi/IBuffer.hpp"

#include <memory>
#include <cstdint>

namespace Synergon::Rhi {
	struct BufferViewDescriptor {
		std::shared_ptr<IBuffer> buffer;

		BufferUsage::Type usage;
		uint64_t          offset;
		uint64_t          size;
	};
};  // namespace Synergon::Rhi
