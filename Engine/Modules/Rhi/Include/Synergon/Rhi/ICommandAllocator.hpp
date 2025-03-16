#ifndef SYNERGON_RHI_ICOMMANDALLOCATOR_HPP
#define SYNERGON_RHI_ICOMMANDALLOCATOR_HPP

#include "Synergon/Rhi/ICommandBuffer.hpp"
#include "Synergon/Rhi/Descriptors/CommandBufferDescriptor.hpp"

#include <memory>

namespace Synergon::Rhi {
	class ICommandAllocator {
	   public:
		virtual ~ICommandAllocator() = default;

		virtual std::unique_ptr<ICommandBuffer> allocateCommandBuffer(const CommandBufferDescriptor& descriptor) = 0;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_ICOMMANDALLOCATOR_HPP
