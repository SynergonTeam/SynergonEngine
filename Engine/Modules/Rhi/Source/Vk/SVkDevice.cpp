#include "SVkDevice.hpp"

#include <stdexcept>
#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>

namespace Synergon::Rhi {
	SVkDevice::SVkDevice() {
	}

	SVkDevice::~SVkDevice() {
		// TODO cleanup should be done in global cleanup function
		cleanupDevice();
	}

	void SVkDevice::waitIdle() const {
		throw std::logic_error("Not implemented yet");
	}

	void SVkDevice::waitForFences(std::span<std::shared_ptr<IFence>> fences) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IDisplay> SVkDevice::createDisplay(const DisplayDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBuffer> SVkDevice::createBuffer(const BufferDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITexture> SVkDevice::createTexture(const TextureDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ISampler> SVkDevice::createSampler(const SamplerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBufferView> SVkDevice::createBufferView(const BufferViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITextureView> SVkDevice::createTextureView(const TextureViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandAllocator> SVkDevice::createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandQueue> SVkDevice::createCommandQueue(const CommandQueueDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShader> SVkDevice::createShader(const ShaderDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputPool> SVkDevice::createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> SVkDevice::createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> SVkDevice::createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputContainer> SVkDevice::createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipelineLayout> SVkDevice::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> SVkDevice::createComputePipeline(const ComputePipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> SVkDevice::createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IFence> SVkDevice::createFence(const FenceDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::string SVkDevice::loadShaderByteCodeFromPath(std::string_view path) const {
		throw std::logic_error("Not implemented yet");
	}

	void SVkDevice::initDevice() {
		createInstance();
		pickPhysicalDevice();
		createLogicalDevice();
	}

	void SVkDevice::createInstance() {
		VkApplicationInfo appInfo{};
		appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName   = "Synergon App";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
		appInfo.pEngineName        = "Synergon Engine";
		appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 1);
		appInfo.apiVersion         = VK_API_VERSION_1_3;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// No extensions or validation layers for simplicity
		createInfo.enabledExtensionCount   = 0;
		createInfo.ppEnabledExtensionNames = nullptr;
		createInfo.enabledLayerCount       = 0;

		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Vulkan instance.");
		}


	}

	void SVkDevice::pickPhysicalDevice() {
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw std::runtime_error("Failed to find GPUs with Vulkan support.");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

		// TODO provide device selection mechanism
		for (const auto &device : devices) {
			if (isDeviceSuitable(device)) {
				m_PhysicalDevice = device;
				break;
			}
		}

		if (m_PhysicalDevice == VK_NULL_HANDLE) {
			throw std::runtime_error("Failed to find a suitable GPU.");
		}
	}

    bool SVkDevice::isDeviceSuitable(VkPhysicalDevice device) {
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		for (uint32_t i = 0; i < queueFamilies.size(); i++) {
			if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				m_GraphicsQueueFamilyIndex = i;
				return true;
			}
		}
		return false;
	}

	void SVkDevice::createLogicalDevice() {
		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = m_GraphicsQueueFamilyIndex;
		queueCreateInfo.queueCount       = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos    = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures     = &deviceFeatures;

		createInfo.enabledExtensionCount = 0;
		createInfo.enabledLayerCount     = 0;

		if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create logical device.");
		}
	}

	void SVkDevice::cleanupDevice() noexcept {
		vkDestroyDevice(m_Device, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}
}  // namespace Synergon::Rhi
