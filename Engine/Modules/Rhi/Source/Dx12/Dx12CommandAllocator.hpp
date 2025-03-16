#ifndef SYNERGON_RHI_DX12COMMANDALLOCATOR_HPP
#define SYNERGON_RHI_DX12COMMANDALLOCATOR_HPP

#include "Synergon/Rhi/ICommandAllocator.hpp"
#include "Synergon/Rhi/Descriptors/CommandBufferDescriptor.hpp"

#include <memory>

namespace Synergon::Rhi {
	class Dx12CommandAllocator final : public ICommandAllocator {
	   public:
		std::unique_ptr<ICommandBuffer> allocateCommandBuffer(CommandBufferDescriptor descriptor) override;

	   private:
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_DX12COMMANDALLOCATOR_HPP
