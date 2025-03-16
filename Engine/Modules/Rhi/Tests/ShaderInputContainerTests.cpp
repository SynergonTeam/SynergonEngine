#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderInputContainerTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		std::vector<ShaderInputLayoutEntry> inputEntry{
		    {0, static_cast<ShaderStage::Type>(ShaderStage::eVertex | ShaderStage::eFragment), ShaderInputType::eStorageBuffer}};

		ShaderInputLayoutDescriptor inputLayoutDescriptor;
		inputLayoutDescriptor.entries = inputEntry;

		const auto inputLayout = device->createShaderInputLayout(inputLayoutDescriptor);

		ShaderInputContainerDescriptor inputContainerDescriptor;
		inputContainerDescriptor.layout = inputLayout;

		ASSERT_NO_THROW(auto shaderInputContainer = device->createShaderInputContainer(inputContainerDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, ShaderInputContainerTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi