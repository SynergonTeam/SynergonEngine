#ifndef SYNERGON_RHI_BUFFERDESCRIPTOR_HPP
#define SYNERGON_RHI_BUFFERDESCRIPTOR_HPP

#include <Synergon/Rhi/Enums.hpp>
#include <cstdint>

namespace Synergon::Rhi {
	struct BufferDescriptor {
		MemoryUsage memoryUsage;
		BufferUsage::Type usage;

		uint64_t size;
	};
}  // namespace Synergon::Rhi

#endif
