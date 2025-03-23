#pragma once

#include "Synergon/Rhi/IDevice.hpp"

namespace Synergon::Rhi {
	class VkDevice final : public IDevice {
	   public:
		VkDevice();
		~VkDevice() override;

		void waitIdle() const override;
		void waitForFences(std::span<std::shared_ptr<IFence>> fences) const override;

		std::unique_ptr<IDisplay> createDisplay(const DisplayDescriptor &descriptor) const override;

		std::shared_ptr<IBuffer>  createBuffer(const BufferDescriptor &descriptor) const override;
		std::shared_ptr<ITexture> createTexture(const TextureDescriptor &descriptor) const override;
		std::shared_ptr<ISampler> createSampler(const SamplerDescriptor &descriptor) const override;

		std::shared_ptr<IBufferView>  createBufferView(const BufferViewDescriptor &descriptor) const override;
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor &descriptor) const override;

		std::unique_ptr<ICommandAllocator> createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const override;
		std::unique_ptr<ICommandQueue>     createCommandQueue(const CommandQueueDescriptor &descriptor) const override;

		std::shared_ptr<IShader> createShader(const ShaderDescriptor &descriptor) const override;

		std::shared_ptr<IShaderInputPool>      createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputContainer> createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const override;

		std::shared_ptr<IPipelineLayout> createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const override;
		std::unique_ptr<IPipeline>       createComputePipeline(const ComputePipelineDescriptor &descriptor) const override;
		std::unique_ptr<IPipeline>       createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const override;

		std::unique_ptr<IFence> createFence(const FenceDescriptor &descriptor) const override;

		std::string loadShaderByteCodeFromPath(std::string_view path) const override;

	   public:
	};

	inline std::unique_ptr<IDevice> CreateVkDevice() {
		return std::make_unique<VkDevice>();
	}

}  // namespace Synergon::Rhi
