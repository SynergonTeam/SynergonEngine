#pragma once

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/ICommandBuffer.hpp"
#include "Synergon/Rhi/IFence.hpp"

#include <memory>

namespace Synergon::Rhi {
	class ICommandQueue {
	   public:
		virtual ~ICommandQueue() = default;

		//! Resets the all the ICommandBuffers allocated using this ICommandAllocator
		//! Any of the ICommandBuffers must not be use and must be submited before resetting the ICommandAllocator
		virtual void reset() const = 0;

		virtual void submit(std::span<std::shared_ptr<ICommandBuffer>> commandBuffers, const std::shared_ptr<IFence>& signal = nullptr, const std::shared_ptr<IFence>& wait = nullptr) const = 0;

		virtual CommandType getCommandType() const = 0;
	};
}  // namespace Synergon::Rhi
