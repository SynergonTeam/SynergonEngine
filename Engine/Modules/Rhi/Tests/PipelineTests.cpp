#include "TestClasses.hpp"
#include "Synergon/Core/FileHelpers.hpp"

namespace Synergon::Rhi {
	TEST_P(PipelineTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = {};
		pipelineLayoutDescriptor.pushConstantRanges = {};

		const std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

		std::vector<char> shaderBuffer;
		shaderBuffer = Core::ReadFile("Assets/Shaders/Triangle.slang");

		ShaderDescriptor vertexShaderDescriptor{};
		vertexShaderDescriptor.type = ShaderCompileType::eRuntime;
		vertexShaderDescriptor.data = shaderBuffer.data();

		const std::shared_ptr<IShader> vertexShader = device->createShader(vertexShaderDescriptor);

		ShaderModule vertexShaderModule{};
		vertexShaderModule.shader     = vertexShader;
		vertexShaderModule.entryPoint = "vsmain";

		ShaderDescriptor fragmentShaderDescriptor{};
		fragmentShaderDescriptor.type = ShaderCompileType::eRuntime;
		fragmentShaderDescriptor.data = shaderBuffer.data();

		const std::shared_ptr<IShader> fragmentShader = device->createShader(vertexShaderDescriptor);

		ShaderModule fragmentShaderModule;
		fragmentShaderModule.shader     = fragmentShader;
		fragmentShaderModule.entryPoint = "fsmain";

		RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
		rasterizerPipelineDescriptor.layout               = layout;
		rasterizerPipelineDescriptor.vertexShaderModule   = vertexShaderModule;
		rasterizerPipelineDescriptor.fragmentShaderModule = fragmentShaderModule;

		EXPECT_NO_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, PipelineTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi