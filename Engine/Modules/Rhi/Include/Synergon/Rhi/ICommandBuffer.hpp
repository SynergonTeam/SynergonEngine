#pragma once

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/IBufferView.hpp"
#include "Synergon/Rhi/IPipeline.hpp"
#include "Synergon/Rhi/IShaderInputContainer.hpp"

#include "Synergon/Rhi/Descriptors/RenderingDescriptor.hpp"

#include <memory>
#include <cstdint>

namespace Synergon::Rhi {
	struct CopyTextureInfo {
		std::shared_ptr<ITexture> texture;

		uint32_t            mipLevel  = 0u;
		uint32_t            origin[3] = {0u, 0u, 0u};
		TextureAspect::Type aspect    = TextureAspect::eColor;
	};

	struct CopyBufferInfo {
		std::shared_ptr<IBuffer> buffer;

		uint32_t offset = 0u;

		uint32_t bytesPerRow;
		uint32_t rowsPerImage;
	};

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

		virtual void executeCommands(std::span<std::shared_ptr<ICommandBuffer>> commandBuffers) const = 0;

		virtual void beginRendering(const RenderingDescriptor& descriptor) const = 0;
		virtual void endRendering() const                                        = 0;

		virtual void setViewport(const Viewport& viewport) const = 0;
		virtual void setScissor(const Scissor& scissor) const    = 0;

		virtual void bindRasterizerPipeline(const std::shared_ptr<IPipeline>& pipeline) const                                             = 0;
		virtual void bindRasterizerShaderInputContainer(uint32_t set, const std::shared_ptr<IShaderInputContainer>& inputContainer) const = 0;
		virtual void bindRasterizerShaderInputContainers(std::span<std::shared_ptr<IShaderInputContainer>> inputContainers) const         = 0;

		virtual void setIndexBuffer(const std::shared_ptr<IBufferView>& buffer, IndexType indexType = IndexType::eUint32) const = 0;
		virtual void setVertexBuffer(uint32_t location, const std::shared_ptr<IBufferView>& buffer) const                       = 0;
		virtual void setVertexBuffers(std::span<std::shared_ptr<IBufferView>> buffers) const                                    = 0;

		virtual void draw(uint32_t vertexCount, uint32_t instanceCount = 1u, uint32_t firstVertex = 0u, uint32_t firstInstance = 0u) const                                 = 0;
		virtual void drawIndexed(uint32_t indexCount, uint32_t instanceCount = 1u, uint32_t firstIndex = 0u, int32_t vertexOffset = 0u, uint32_t firstInstance = 0u) const = 0;
		// TODO: drawIndrect

		virtual void bindComputePipeline(const std::shared_ptr<IPipeline>& pipeline) const                                             = 0;
		virtual void bindComputeShaderInputContainer(uint32_t set, const std::shared_ptr<IShaderInputContainer>& inputContainer) const = 0;
		virtual void bindComputeShaderInputContainers(std::span<std::shared_ptr<IShaderInputContainer>> inputContainers) const         = 0;

		virtual void dispatchComputeWorkgroups(uint32_t groupCountX, uint32_t groupCountY = 1u, uint32_t groupCountZ = 1u) const = 0;

		virtual void copyBufferToBuffer(const std::shared_ptr<IBuffer>& source, uint32_t sourceOffset, const std::shared_ptr<IBuffer>& destination, uint32_t destinationOffset, uint32_t size) const = 0;
		virtual void copyBufferToTexture(const CopyBufferInfo& source, const CopyTextureInfo& destination, uint32_t size[3]) const                                                                   = 0;
		virtual void copyTextureToBuffer(const CopyTextureInfo& source, const CopyBufferInfo& destination, uint32_t size[3]) const                                                                   = 0;
		virtual void copyTextureToTexture(const CopyTextureInfo& source, const CopyTextureInfo& destination, uint32_t size[3]) const                                                                 = 0;
	};
}  // namespace Synergon::Rhi
