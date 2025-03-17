#include "VkDevice.hpp"

#include <stdexcept>

namespace Synergon::Rhi {
	VkDevice::VkDevice() {
	}

	VkDevice::~VkDevice() {
	}

	std::unique_ptr<IDisplay> VkDevice::createDisplay(const DisplayDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IBuffer> VkDevice::createBuffer(const BufferDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ITexture> VkDevice::createTexture(const TextureDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ISampler> VkDevice::createSampler(const SamplerDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<ITextureView> VkDevice::createTextureView(const TextureViewDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<ICommandAllocator> VkDevice::createCommandAllocator(const CommandAllocatorDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<ICommandQueue> VkDevice::createCommandQueue(const CommandQueueDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IPipelineLayout> VkDevice::createPipelineLayout(const PipelineLayoutDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IPipeline> VkDevice::createRasterizerPipeline(const RasterizerPipelineDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IPipeline> VkDevice::createComputePipeline(const ComputePipelineDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IShader> VkDevice::createShader(const ShaderDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IShaderInputLayout> VkDevice::createShaderInputLayout(const ShaderInputLayoutDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::shared_ptr<IShaderInputContainer> VkDevice::createShaderInputContainer(const ShaderInputContainerDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

	std::unique_ptr<IFence> VkDevice::createFence(const FenceDescriptor& descriptor) {
		throw std::logic_error("Not implemented");
	}

}  // namespace Synergon::Rhi
