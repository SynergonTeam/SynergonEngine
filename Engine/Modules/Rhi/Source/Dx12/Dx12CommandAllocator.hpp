#pragma once

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
