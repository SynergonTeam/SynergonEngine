#ifndef SYNERGON_RHI_IDEVICE_HPP
#define SYNERGON_RHI_IDEVICE_HPP

#include "Descriptors/BufferDescriptor.hpp"
#include "Descriptors/CommandAllocatorDescriptor.hpp"
#include "Descriptors/CommandQueueDescriptor.hpp"
#include "Descriptors/TextureDescriptor.hpp"
#include "Descriptors/PipelineDescriptor.hpp"
#include "Descriptors/PipelineLayoutDescriptor.hpp"
#include "Descriptors/ShaderInputContainerDescriptor.hpp"
#include "Descriptors/ShaderInputLayoutDescriptor.hpp"
#include "Descriptors/SamplerDescriptor.hpp"
#include "Descriptors/DisplayDescriptor.hpp"
#include "Descriptors/FenceDescriptor.hpp"
#include "Descriptors/TextureViewDescriptor.hpp"

#include "IBuffer.hpp"
#include "ICommandAllocator.hpp"
#include "ICommandQueue.hpp"
#include "IDisplay.hpp"
#include "IFence.hpp"
#include "IPipeline.hpp"
#include "IPipelineLayout.hpp"
#include "ISampler.hpp"
#include "IShaderInputContainer.hpp"
#include "ITexture.hpp"
#include "ITextureView.hpp"

#include <memory>


namespace Synergon::Rhi {
	class IDevice {
	public:
		virtual ~IDevice() = default;

		virtual std::unique_ptr<IDisplay> createDisplay(const DisplayDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IBuffer> createBuffer(const BufferDescriptor& descriptor) = 0;
		virtual std::shared_ptr<ITexture> createTexture(const TextureDescriptor& descriptor) = 0;
		virtual std::shared_ptr<ISampler> createSampler(const SamplerDescriptor& descriptor) = 0;

		virtual std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor) = 0;

		virtual std::unique_ptr<ICommandAllocator> createCommandAllocator(const CommandAllocatorDescriptor& descriptor) = 0;
		virtual std::unique_ptr<ICommandQueue> createCommandQueue(const CommandQueueDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IPipelineLayout> createPipelineLayout(const PipelineLayoutDescriptor& descriptor) = 0;
		virtual std::unique_ptr<IPipeline> createRasterizerPipeline(const RasterizerPipelineDescriptor& descriptor) = 0;
		virtual std::unique_ptr<IPipeline> createComputePipeline(const ComputePipelineDescriptor& descriptor) = 0;

		virtual std::unique_ptr<IFence> createFence(const FenceDescriptor& descriptor) = 0;

		virtual std::shared_ptr<IShaderInputLayout> createShaderInputLayout(const ShaderInputLayoutDescriptor& descriptor) = 0;
		virtual std::shared_ptr<IShaderInputContainer> createShaderInputContainer(const ShaderInputContainerDescriptor& descriptor) = 0;

	protected:
		IDevice() = default;
	};
}

#endif //#ifndef SYNERGON_RHI_IDEVICE_HPP
