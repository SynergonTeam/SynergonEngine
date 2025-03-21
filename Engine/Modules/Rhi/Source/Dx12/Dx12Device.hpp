#pragma once

#include "Synergon/Rhi/IDevice.hpp"

namespace Synergon::Rhi {
	class Dx12Device final : public IDevice {
	   public:
		std::unique_ptr<IDisplay>              createDisplay(const DisplayDescriptor &descriptor) override;
		std::shared_ptr<IBuffer>               createBuffer(const BufferDescriptor &descriptor) override;
		std::shared_ptr<ITexture>              createTexture(const TextureDescriptor &descriptor) override;
		std::shared_ptr<ISampler>              createSampler(const SamplerDescriptor &descriptor) override;

		std::shared_ptr<IBufferView>           createBufferView(const BufferViewDescriptor &descriptor) override;
		std::shared_ptr<ITextureView>          createTextureView(const TextureViewDescriptor &descriptor) override;

		std::unique_ptr<ICommandAllocator>     createCommandAllocator(const CommandAllocatorDescriptor &descriptor) override;
		std::unique_ptr<ICommandQueue>         createCommandQueue(const CommandQueueDescriptor &descriptor) override;

		std::shared_ptr<IShader>               createShader(const ShaderDescriptor &descriptor) override;

		std::shared_ptr<IShaderInputPool>      createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) override;
		std::shared_ptr<IShaderInputContainer> createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) override;

		std::shared_ptr<IPipelineLayout>       createPipelineLayout(const PipelineLayoutDescriptor &descriptor) override;
		std::unique_ptr<IPipeline>             createComputePipeline(const ComputePipelineDescriptor &descriptor) override;
		std::unique_ptr<IPipeline>             createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) override;

		std::unique_ptr<IFence>                createFence(const FenceDescriptor &descriptor) override;

		std::string                            loadShaderByteCodeFromPath(std::string_view path) override;

		std::string loadShaderByteCodeFromPath(std::string_view path) override;

	   private:
	};

	inline std::unique_ptr<IDevice> CreateDx12Device() {
		return std::make_unique<Dx12Device>();
	}

}  // namespace Synergon::Rhi
