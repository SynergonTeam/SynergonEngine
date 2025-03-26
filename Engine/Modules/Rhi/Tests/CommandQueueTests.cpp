#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(CommandQueueTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr CommandAllocatorDescriptor descriptor{};

		const std::unique_ptr<ICommandAllocator> allocator = device->createCommandAllocator(descriptor);

		constexpr CommandBufferDescriptor commandBufferDescriptor{};

		ASSERT_NO_THROW(std::unique_ptr<ICommandBuffer> commandBuffer = allocator->allocateCommandBuffer(commandBufferDescriptor));
	}
}  // namespace Synergon::Rhi
