#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(PipelineTest, EmptyLayoutDefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		std::vector<std::shared_ptr<IShaderInputLayout>> inputLayouts       = {};
		std::vector<PushConstantRange>                   pushConstantRanges = {};

		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = inputLayouts;
		pipelineLayoutDescriptor.pushConstantRanges = pushConstantRanges;

		std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

		RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
		rasterizerPipelineDescriptor.layout = layout;

		EXPECT_NO_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
	}

	TEST_P(PipelineTest, ComputeEmptyConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = {};
		pipelineLayoutDescriptor.pushConstantRanges = {};

		const std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

		ComputePipelineDescriptor computePipelineDescriptor;
		computePipelineDescriptor.layout       = layout;
		computePipelineDescriptor.shaderModule = {};  // Empty/dummy shader descriptor
		// computePipelineDescriptor.entryPoint = "main";

		EXPECT_NO_THROW(device->createComputePipeline(computePipelineDescriptor));
	}

	TEST_P(PipelineTest, RasterizerNullLayout) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		RasterizerPipelineDescriptor rasterizerPipelineDescriptor;
		rasterizerPipelineDescriptor.layout                 = nullptr;  // intentionally null
		rasterizerPipelineDescriptor.inputLayouts           = {};
		rasterizerPipelineDescriptor.vertexShaderModule     = {};
		rasterizerPipelineDescriptor.fragmentShaderModule   = {};
		rasterizerPipelineDescriptor.colorAttachmentFormats = {};
		rasterizerPipelineDescriptor.depthStencil           = {};
		rasterizerPipelineDescriptor.rasterizer             = {};
		rasterizerPipelineDescriptor.colorBlend             = {};
		rasterizerPipelineDescriptor.multisample            = {};

		EXPECT_ANY_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
	}

	TEST_P(PipelineTest, ComputeNullLayout) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		ComputePipelineDescriptor computePipelineDescriptor;
		computePipelineDescriptor.layout              = nullptr;
		computePipelineDescriptor.computeShaderModule = {};
		// computePipelineDescriptor.entryPoint = "main";

		EXPECT_ANY_THROW(device->createComputePipeline(computePipelineDescriptor));
	}

	TEST_P(PipelineTest, RasterizerWithVertexInputAndDepthStencil) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		// Create pipeline layout.
		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = {};
		pipelineLayoutDescriptor.pushConstantRanges = {};
		std::shared_ptr<IPipelineLayout> layout     = device->createPipelineLayout(pipelineLayoutDescriptor);

		std::vector<VertexAttribute> vertexAttributes = {
		    {VertexFormat::eUint8, 0, 0}};

		std::vector<VertexInputLayout> inputLayouts = {
		    {VertexStepMode::eVertex, sizeof(uint8_t), std::span(vertexAttributes)}};

		DepthStencilState depthStencilState{};
		depthStencilState.format            = TextureFormat::eDepth32Float;
		depthStencilState.depthTestEnable   = true;
		depthStencilState.depthWriteEnable  = true;
		depthStencilState.minDepthBounds    = 0.0f;
		depthStencilState.maxDepthBounds    = 1.0f;
		depthStencilState.depthCompareOp    = CompareOp::eLess;
		depthStencilState.stencilTestEnable = false;
		depthStencilState.stencilReadMask   = 0xff;
		depthStencilState.stencilWriteMask  = 0xff;
		// Initialize stencil face states.
		depthStencilState.front = {CompareOp::eAlways, StencilOp::eKeep, StencilOp::eKeep, StencilOp::eKeep};
		depthStencilState.back  = {CompareOp::eAlways, StencilOp::eKeep, StencilOp::eKeep, StencilOp::eKeep};

		RasterizerPipelineDescriptor rasterizerPipelineDescriptor;
		rasterizerPipelineDescriptor.layout                 = layout;
		rasterizerPipelineDescriptor.inputLayouts           = std::span<VertexInputLayout>(inputLayouts);
		rasterizerPipelineDescriptor.vertexShaderModule     = {};  // todo: create dummy shader descriptor
		rasterizerPipelineDescriptor.fragmentShaderModule   = {};  // todo: create dummy shader descriptor
		std::vector colorFormats                            = {TextureFormat::eRGBA8Unorm};
		rasterizerPipelineDescriptor.colorAttachmentFormats = std::span<TextureFormat>(colorFormats);
		rasterizerPipelineDescriptor.depthStencil           = depthStencilState;
		rasterizerPipelineDescriptor.rasterizer.topology    = PrimitiveTopology::eTriangleList;
		rasterizerPipelineDescriptor.rasterizer.cullMode    = CullMode::eBack;
		rasterizerPipelineDescriptor.rasterizer.frontFace   = FrontFace::eClockWise;
		rasterizerPipelineDescriptor.rasterizer.polygonMode = PolygoneMode::eFill;
		// Use default color blend and multisample states.
		rasterizerPipelineDescriptor.colorBlend  = {};
		rasterizerPipelineDescriptor.multisample = {};

		EXPECT_NO_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, PipelineTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi