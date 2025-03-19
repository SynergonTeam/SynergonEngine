#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderInputContainerTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));


		std::shared_ptr<IShaderInputLayout> inputLayout;
		{
			std::vector<ShaderResourceInputLayoutEntry> inputEntry{
			    {0, static_cast<ShaderStage::Type>(ShaderStage::eVertex | ShaderStage::eFragment), ShaderResourceInputType::eStorageBuffer }
			};

			ShaderResourceInputLayoutDescriptor inputLayoutDescriptor;
			inputLayoutDescriptor.resourceEntries = inputEntry;

			inputLayout = device->createShaderInputLayout(inputLayoutDescriptor);
		}

		std::shared_ptr<IShaderInputPool> pool;
		{
			ShaderInputPoolDescriptor shaderInputPoolDesc{};
			shaderInputPoolDesc.type = ShaderInputType::eResource;
			shaderInputPoolDesc.count = 100;

			pool = device->createShaderInputPool(shaderInputPoolDesc);
		}

		ShaderInputContainerDescriptor inputContainerDescriptor;
		inputContainerDescriptor.layout = inputLayout;
		inputContainerDescriptor.pool = pool;

		ASSERT_NO_THROW(auto shaderInputContainer = device->createShaderInputContainer(inputContainerDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, ShaderInputContainerTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi