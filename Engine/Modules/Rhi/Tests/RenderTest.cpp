#include "TestClasses.hpp"
#include "Synergon/Core/FileHelpers.hpp"

namespace Synergon::Rhi {
	TEST_P(RenderTest, DefaultConstruction) {
		const std::string        apiName = GetParam();
		std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		// display creation
		std::unique_ptr<IDisplay> display;
		{
			DisplayDescriptor displayDescriptor;
			displayDescriptor.windowHandle = nullptr;

			display = device->createDisplay(displayDescriptor);
		}

		std::shared_ptr<IPipelineLayout>    layout;
		std::shared_ptr<IShaderInputLayout> sceneDataSamplerInputLayout;
		std::shared_ptr<IShaderInputLayout> sceneDataResourcesInputLayout;
		// layout
		{
			// scene data layout
			{
				ShaderResourceInputLayoutDescriptor shaderInputLayoutDescriptor;

				std::vector<ShaderResourceInputLayoutEntry> resourceEntries = {
				    {0, ShaderStage::eVertex, ShaderResourceInputType::eStorageBuffer},     // instance matrices
				    {1, ShaderStage::eFragment, ShaderResourceInputType::eSampledTexture},  // texture
				};

				shaderInputLayoutDescriptor.resourceEntries = resourceEntries;
				sceneDataResourcesInputLayout               = device->createShaderInputLayout(shaderInputLayoutDescriptor);
			}

			{
				std::vector<uint32_t> samplerBindings = {2};

				ShaderSamplerInputLayoutDescriptor samplerInputLayoutDescriptor;
				samplerInputLayoutDescriptor.samplerBindings = samplerBindings;

				// todo: I really think that we should directly pass vector of sampler bindings, users won't like this
				sceneDataSamplerInputLayout = device->createShaderInputLayout(samplerInputLayoutDescriptor);
			}

			// pipeline layout creation
			{
				std::vector shaderInputLayouts{
				    sceneDataResourcesInputLayout,
				    sceneDataSamplerInputLayout};

				PipelineLayoutDescriptor pipelineLayoutDescriptor;
				pipelineLayoutDescriptor.shaderInputLayouts = shaderInputLayouts;
				pipelineLayoutDescriptor.pushConstantRanges = {};

				layout = device->createPipelineLayout(pipelineLayoutDescriptor);
			}
		}

		ShaderModule vertexShaderModule{};
		ShaderModule fragmentShaderModule{};
		// shader module creation
		{
			std::vector<char> shaderBuffer;
			shaderBuffer = Core::ReadFile("Assets/Shaders/Triangle.slang");

			ShaderDescriptor vertexShaderDescriptor{};
			vertexShaderDescriptor.type = ShaderCodeType::eShaderSlang;
			vertexShaderDescriptor.data = shaderBuffer.data();

			ShaderDescriptor fragmentShaderDescriptor{};
			fragmentShaderDescriptor.type = ShaderCodeType::eShaderSlang;
			fragmentShaderDescriptor.data = shaderBuffer.data();

			std::shared_ptr<IShader> vertexShader   = device->createShader(vertexShaderDescriptor);
			std::shared_ptr<IShader> fragmentShader = device->createShader(vertexShaderDescriptor);

			fragmentShaderModule.shader     = fragmentShader;
			fragmentShaderModule.entryPoint = "fsmain";

			vertexShaderModule.shader     = vertexShader;
			vertexShaderModule.entryPoint = "vsmain";
		}

		// todo: multiple vertex layouts for one pipeline might not be supported for dx12
		std::vector<VertexInputLayout> vertexInputLayouts;
		{
			std::vector<VertexAttribute> vertexAttributes{
			    {VertexFormat::eFloat32x4, 0, 0},
			    {VertexFormat::eFloat32x4, 16, 0},
			    {VertexFormat::eFloat32x2, 32, 0},
			};

			VertexInputLayout vertexInputLayout;
			vertexInputLayout.attributes  = vertexAttributes;
			vertexInputLayout.arrayStride = 48;
		}

		std::unique_ptr<IPipeline> pipeline;
		// pipeline creation
		{
			RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
			rasterizerPipelineDescriptor.layout               = layout;
			rasterizerPipelineDescriptor.vertexShaderModule   = vertexShaderModule;
			rasterizerPipelineDescriptor.fragmentShaderModule = fragmentShaderModule;
			// todo: multiple vertex layouts for one pipeline might not be supported for dx12
			rasterizerPipelineDescriptor.inputLayouts = vertexInputLayouts;

			pipeline = device->createRasterizerPipeline(rasterizerPipelineDescriptor);
		}

		std::shared_ptr<IShaderInputPool> resourceShaderInputPool;
		{
			ShaderInputPoolDescriptor shaderInputPoolDesc{};
			shaderInputPoolDesc.type  = ShaderInputType::eResource;
			shaderInputPoolDesc.count = 100;

			resourceShaderInputPool = device->createShaderInputPool(shaderInputPoolDesc);
		}

		std::shared_ptr<IShaderInputPool> samplerShaderInputPool;
		{
			ShaderInputPoolDescriptor shaderInputPoolDesc{};
			shaderInputPoolDesc.type  = ShaderInputType::eSampler;
			shaderInputPoolDesc.count = 100;

			samplerShaderInputPool = device->createShaderInputPool(shaderInputPoolDesc);
		}

		std::shared_ptr<IShaderInputContainer> resourceInputContainer;
		{
			ShaderInputContainerDescriptor resourceInputContainerDescriptor;
			resourceInputContainerDescriptor.layout = sceneDataResourcesInputLayout;
			resourceInputContainerDescriptor.pool   = resourceShaderInputPool;

			resourceInputContainer = device->createShaderInputContainer(resourceInputContainerDescriptor);
		}
		std::shared_ptr<IShaderInputContainer> samplerInputContainer;
		{
			ShaderInputContainerDescriptor resourceInputContainerDescriptor;
			resourceInputContainerDescriptor.layout = sceneDataSamplerInputLayout;
			resourceInputContainerDescriptor.pool   = samplerShaderInputPool;

			samplerInputContainer = device->createShaderInputContainer(resourceInputContainerDescriptor);
		}

		// todo: buffer and texture creation
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, RenderTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi
