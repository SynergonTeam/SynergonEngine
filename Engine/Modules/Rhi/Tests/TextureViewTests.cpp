#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(TextureViewTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr TextureDescriptor textureDescriptor{};
		std::shared_ptr<ITexture>   texture = device->createTexture(textureDescriptor);

		constexpr TextureViewDescriptor viewDescriptor{};

		ASSERT_NO_THROW(std::shared_ptr<ITextureView> textureView = device->createTextureView(viewDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, TextureViewTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi
