#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderInputLayoutTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		std::vector<ShaderResourceInputLayoutEntry> inputEntry{
		    {0, static_cast<ShaderStage::Type>(ShaderStage::eVertex | ShaderStage::eFragment), ShaderResourceInputType::eStorageBuffer}};

		ShaderResourceInputLayoutDescriptor inputLayoutDescriptor;
		inputLayoutDescriptor.resourceEntries = inputEntry;

		ASSERT_NO_THROW(auto inputLayout = device->createShaderInputLayout(inputLayoutDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, ShaderInputLayoutTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi