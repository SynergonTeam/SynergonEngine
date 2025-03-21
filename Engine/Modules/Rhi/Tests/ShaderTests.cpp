#include "TestClasses.hpp"
#include "Synergon/Core/FileHelpers.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderTest, DefaultConstructionRuntime) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		auto shaderByteCode = device->loadShaderByteCodeFromPath("Assets/Shaders/Triangle");

		ShaderDescriptor vertexShaderDescriptor{};
		vertexShaderDescriptor.type = ShaderCodeType::eNativeByteCode;
		vertexShaderDescriptor.data = shaderByteCode;

		EXPECT_NO_THROW(std::shared_ptr<IShader> vertexShader = device->createShader(vertexShaderDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, ShaderTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi