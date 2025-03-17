#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(PipelineTest, ComputeEmptyConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = {};
		pipelineLayoutDescriptor.pushConstantRanges = {};

		const std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

		ShaderDescriptor shaderDescriptor{};
		shaderDescriptor.data = nullptr;
		shaderDescriptor.size = 0;

		const std::shared_ptr<IShader> shader = device->createShader(shaderDescriptor);

		ShaderModule shaderModule;
		shaderModule.shader     = shader;
		shaderModule.entryPoint = "main";

		ComputePipelineDescriptor computePipelineDescriptor{};
		computePipelineDescriptor.layout       = layout;
		computePipelineDescriptor.shaderModule = shaderModule;

		EXPECT_NO_THROW(device->createComputePipeline(computePipelineDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, PipelineTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi