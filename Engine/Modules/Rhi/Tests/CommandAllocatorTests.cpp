#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(CommandAllocatorTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::shared_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr CommandAllocatorDescriptor descriptor{};

		EXPECT_NO_THROW(std::shared_ptr<ICommandAllocator> sampler = device->createCommandAllocator(descriptor));
	}
}  // namespace Synergon::Rhi