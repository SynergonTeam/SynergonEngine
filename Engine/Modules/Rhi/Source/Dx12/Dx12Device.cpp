#include "Dx12Device.hpp"

#include <stdexcept>

namespace Synergon::Rhi {
	Dx12Device::Dx12Device() {
	}

	Dx12Device::~Dx12Device() {
	}

	std::unique_ptr<IDisplay> Dx12Device::createDisplay(const DisplayDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IBuffer> Dx12Device::createBuffer(const BufferDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ITexture> Dx12Device::createTexture(const TextureDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ISampler> Dx12Device::createSampler(const SamplerDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ITextureView> Dx12Device::createTextureView(const TextureViewDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<ICommandAllocator> Dx12Device::createCommandAllocator(const CommandAllocatorDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<ICommandQueue> Dx12Device::createCommandQueue(const CommandQueueDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IPipelineLayout> Dx12Device::createPipelineLayout(const PipelineLayoutDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IPipeline> Dx12Device::createRasterizerPipeline(const RasterizerPipelineDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IPipeline> Dx12Device::createComputePipeline(const ComputePipelineDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IFence> Dx12Device::createFence(const FenceDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IShaderInputLayout> Dx12Device::createShaderInputLayout(const ShaderInputLayoutDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IShaderInputContainer> Dx12Device::createShaderInputContainer(const ShaderInputContainerDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

}  // namespace Synergon::Rhi
