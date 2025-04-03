#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(CommandAllocatorTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::shared_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr CommandAllocatorDescriptor descriptor{};

		EXPECT_NO_THROW(std::shared_ptr<ICommandAllocator> sampler = device->createCommandAllocator(descriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, CommandAllocatorTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi