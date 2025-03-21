#pragma once

#include "Synergon/Rhi/ICommandBuffer.hpp"
#include "Synergon/Rhi/Descriptors/CommandBufferDescriptor.hpp"

#include <memory>

namespace Synergon::Rhi {
	class ICommandAllocator {
	   public:
		virtual ~ICommandAllocator() = default;

		virtual void reset() const = 0;

		virtual std::unique_ptr<ICommandBuffer> allocateCommandBuffer(const CommandBufferDescriptor& descriptor) const = 0;

		virtual CommandType getCommandType() const = 0;
	};
}  // namespace Synergon::Rhi
