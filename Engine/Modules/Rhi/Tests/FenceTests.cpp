#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(FenceTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr FenceDescriptor descriptor{};

		ASSERT_NO_THROW(auto fence = device->createFence(descriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, FenceTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi
