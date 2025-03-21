#ifndef SYNERGON_RHI_IDEVICE_HPP
#define SYNERGON_RHI_IDEVICE_HPP

#include "Synergon/Rhi/Descriptors/BufferDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/BufferViewDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/CommandAllocatorDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/CommandBufferDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/CommandQueueDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/DisplayDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/FenceDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/PipelineDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/PipelineLayoutDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/SamplerDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/ShaderDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/ShaderInputContainerDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/ShaderInputLayoutDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/ShaderInputPoolDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/TextureDescriptor.hpp"
#include "Synergon/Rhi/Descriptors/TextureViewDescriptor.hpp"

#include "Synergon/Rhi/IBuffer.hpp"
#include "Synergon/Rhi/IBufferView.hpp"
#include "Synergon/Rhi/ICommandAllocator.hpp"
#include "Synergon/Rhi/ICommandBuffer.hpp"
#include "Synergon/Rhi/ICommandQueue.hpp"
#include "Synergon/Rhi/IDisplay.hpp"
#include "Synergon/Rhi/IFence.hpp"
#include "Synergon/Rhi/IPipeline.hpp"
#include "Synergon/Rhi/IPipelineLayout.hpp"
#include "Synergon/Rhi/ISampler.hpp"
#include "Synergon/Rhi/IShader.hpp"
#include "Synergon/Rhi/IShaderInputContainer.hpp"
#include "Synergon/Rhi/IShaderInputLayout.hpp"
#include "Synergon/Rhi/IShaderInputPool.hpp"
#include "Synergon/Rhi/ITexture.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

namespace Synergon::Rhi {
	class IDevice {
	   public:
		virtual ~IDevice() = default;

		virtual std::unique_ptr<IDisplay> createDisplay(const DisplayDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IBuffer>  createBuffer(const BufferDescriptor& descriptor)   = 0;
		virtual std::shared_ptr<ITexture> createTexture(const TextureDescriptor& descriptor) = 0;
		virtual std::shared_ptr<ISampler> createSampler(const SamplerDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IBufferView>  createBufferView(const BufferViewDescriptor& descriptor)   = 0;
		virtual std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor) = 0;

		virtual std::unique_ptr<ICommandAllocator> createCommandAllocator(const CommandAllocatorDescriptor& descriptor) = 0;
		virtual std::unique_ptr<ICommandQueue>     createCommandQueue(const CommandQueueDescriptor& descriptor)         = 0;

		virtual std::shared_ptr<IShader> createShader(const ShaderDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IShaderInputPool>      createShaderInputPool(const ShaderInputPoolDescriptor& descriptor)             = 0;
		virtual std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderResourceInputLayoutDescriptor& descriptor) = 0;
		virtual std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor& descriptor)  = 0;
		virtual std::shared_ptr<IShaderInputContainer> createShaderInputContainer(const ShaderInputContainerDescriptor& descriptor)   = 0;

		virtual std::shared_ptr<IPipelineLayout> createPipelineLayout(const PipelineLayoutDescriptor& descriptor)         = 0;
		virtual std::unique_ptr<IPipeline>       createComputePipeline(const ComputePipelineDescriptor& descriptor)       = 0;
		virtual std::unique_ptr<IPipeline>       createRasterizerPipeline(const RasterizerPipelineDescriptor& descriptor) = 0;

		virtual std::unique_ptr<IFence> createFence(const FenceDescriptor& descriptor) = 0;

		virtual std::string loadShaderFromPath(std::string_view path) = 0;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_IDEVICE_HPP
