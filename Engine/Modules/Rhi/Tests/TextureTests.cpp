#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(TextureTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr TextureDescriptor descriptor{};

		ASSERT_NO_THROW(std::shared_ptr<ITexture> texture = device->createTexture(descriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, TextureTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi