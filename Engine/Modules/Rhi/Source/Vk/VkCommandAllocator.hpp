#pragma once

#include "Synergon/Rhi/ICommandAllocator.hpp"

#include <memory>

namespace Synergon::Rhi {
	class VkCommandAllocator final : public ICommandAllocator {
	   public:
		std::unique_ptr<ICommandBuffer> allocateCommandBuffer(const CommandBufferDescriptor &descriptor) override;
	};
}  // namespace Synergon::Rhi
