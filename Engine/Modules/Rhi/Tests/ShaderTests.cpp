#include "TestClasses.hpp"
#include "Synergon/Core/FileHelpers.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderTest, DefaultConstructionRuntime) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		std::vector<char> shaderBuffer;
		shaderBuffer = Core::ReadFile("Assets/Shaders/Triangle.slang");

		ShaderDescriptor vertexShaderDescriptor{};
		vertexShaderDescriptor.type = ShaderCodeType::eShaderSlang;
		vertexShaderDescriptor.data = shaderBuffer.data();

		EXPECT_NO_THROW(std::shared_ptr<IShader> vertexShader = device->createShader(vertexShaderDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, ShaderTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi