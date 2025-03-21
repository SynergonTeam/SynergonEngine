#ifndef SYNERGON_ENGINE_BUFFERVIEWDESCRIPTOR_HPP
#define SYNERGON_ENGINE_BUFFERVIEWDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

#include "Synergon/Rhi/IShaderInputPool.hpp"

#include <memory>
#include <cstdint>

namespace Synergon::Rhi {
	struct BufferViewDescriptor {
		std::shared_ptr<IShaderInputPool> inputPool;

		BufferUsage::Type usage;
		uint64_t          offset;
		uint64_t          size;
	};
};  // namespace Synergon::Rhi

#endif  // SYNERGON_ENGINE_BUFFERVIEWDESCRIPTOR_HPP
