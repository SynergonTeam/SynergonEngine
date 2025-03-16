#ifndef SYNERGON_RHI_ICOMMANDALLOCATOR_HPP
#define SYNERGON_RHI_ICOMMANDALLOCATOR_HPP

#include "ICommandBuffer.hpp"
#include "Descriptors/CommandBufferDescriptor.hpp"

#include <memory>


namespace Synergon::Rhi {
	class ICommandAllocator {
	public:
		virtual ~ICommandAllocator() = default;
		virtual std::unique_ptr<ICommandBuffer> allocateCommandBuffer(CommandBufferDescriptor descriptor) = 0;
	private:
	};
}

#endif //#ifndef SYNERGON_RHI_ICOMMANDALLOCATOR_HPP
