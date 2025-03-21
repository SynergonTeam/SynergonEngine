#ifndef SYNERGON_RHI_ICOMMANDQUEUE_HPP
#define SYNERGON_RHI_ICOMMANDQUEUE_HPP

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/ICommandBuffer.hpp"
#include "Synergon/Rhi/IFence.hpp"

#include <memory>

namespace Synergon::Rhi {
	class ICommandQueue {
	   public:
		virtual ~ICommandQueue() = default;

		virtual void submit(std::span<std::shared_ptr<ICommandBuffer>> commandBuffers, const std::shared_ptr<IFence>& signal) const = 0;

		virtual CommandType getCommandType() const = 0;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_ICOMMANDQUEUE_HPP
