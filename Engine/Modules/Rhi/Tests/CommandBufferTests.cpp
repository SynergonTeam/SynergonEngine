#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(CommandBufferTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr CommandAllocatorDescriptor descriptor{};

		const std::unique_ptr<ICommandAllocator> allocator = device->createCommandAllocator(descriptor);

		constexpr CommandBufferDescriptor commandBufferDescriptor{};

		ASSERT_NO_THROW(std::unique_ptr<ICommandBuffer> commandBuffer = allocator->allocateCommandBuffer(commandBufferDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, CommandBufferTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi
