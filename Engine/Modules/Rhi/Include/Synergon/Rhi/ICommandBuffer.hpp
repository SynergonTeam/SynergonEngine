#ifndef SYNERGON_RHI_ICOMMAND_HPP
#define SYNERGON_RHI_ICOMMAND_HPP

#include "Synergon/Rhi/IBuffer.hpp"
#include "Synergon/Rhi/IPipeline.hpp"
#include "Synergon/Rhi/IShaderInputContainer.hpp"

#include "Synergon/Rhi/Descriptors/RenderingDescriptor.hpp"

#include <memory>
#include <cstdint>

namespace Synergon::Rhi {
	struct Viewport {
		uint32_t x = 0u;
		uint32_t y = 0u;

		uint32_t width;
		uint32_t height;

		float minDepth = 0.0f;
		float maxDepth = 1.0f;
	};

	struct Scissor {
		uint32_t x = 0u;
		uint32_t y = 0u;

		uint32_t width;
		uint32_t height;
	};

	class ICommandBuffer {
	   public:
		virtual ~ICommandBuffer() = default;

		virtual void reset() const = 0;

		virtual void open() const  = 0;
		virtual void close() const = 0;

		virtual void beginRendering(const RenderingDescriptor& descriptor) const = 0;
		virtual void endRendering() const                                        = 0;

		virtual void setViewport(const Viewport& viewport) const = 0;
		virtual void setScissor(const Scissor& scissor) const    = 0;

		virtual void bindPipeline(const std::shared_ptr<IPipeline>& pipeline) const                                     = 0;
		virtual void bindShaderInputContainers(std::span<std::shared_ptr<IShaderInputContainer>> inputContainers) const = 0;

		virtual void setVertexBuffers(std::span<std::shared_ptr<IBuffer>> buffers) const = 0;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_ICOMMAND_HPP
