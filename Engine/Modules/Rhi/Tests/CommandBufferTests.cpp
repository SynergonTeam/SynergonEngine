#include "TestApiClasses.hpp"

#include "Utils.hpp"

#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

namespace Synergon::Rhi {
	TEST_P(CommandBufferTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr CommandAllocatorDescriptor descriptor{};

		const std::shared_ptr<ICommandAllocator> allocator = device->createCommandAllocator(descriptor);

		constexpr CommandBufferDescriptor commandBufferDescriptor{};

		ASSERT_NO_THROW(std::shared_ptr<ICommandBuffer> commandBuffer = allocator->allocateCommandBuffer(commandBufferDescriptor));
	}
}  // namespace Synergon::Rhi
