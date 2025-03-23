#include "Dx12Device.hpp"

#include <stdexcept>

namespace Synergon::Rhi {
	Dx12Device::Dx12Device() {}

	Dx12Device::~Dx12Device() {}

	void Dx12Device::waitIdle() const {
		throw std::logic_error("Not implemented yet");
	}

	void Dx12Device::waitForFences(std::span<std::shared_ptr<IFence>> fences) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IDisplay> Dx12Device::createDisplay(const DisplayDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBuffer> Dx12Device::createBuffer(const BufferDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITexture> Dx12Device::createTexture(const TextureDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ISampler> Dx12Device::createSampler(const SamplerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBufferView> Dx12Device::createBufferView(const BufferViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITextureView> Dx12Device::createTextureView(const TextureViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandAllocator> Dx12Device::createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandQueue> Dx12Device::createCommandQueue(const CommandQueueDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShader> Dx12Device::createShader(const ShaderDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputPool> Dx12Device::createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> Dx12Device::createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> Dx12Device::createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputContainer> Dx12Device::createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipelineLayout> Dx12Device::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> Dx12Device::createComputePipeline(const ComputePipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> Dx12Device::createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IFence> Dx12Device::createFence(const FenceDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::string Dx12Device::loadShaderByteCodeFromPath(std::string_view path) const {
		throw std::logic_error("Not implemented yet");
	}
}  // namespace Synergon::Rhi
