#include "TestClasses.hpp"
#include "Synergon/Core/FileHelpers.hpp"

#include <array>

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
				std::vector<uint32_t> samplerBindings = {0};

				ShaderSamplerInputLayoutDescriptor samplerInputLayoutDescriptor;
				samplerInputLayoutDescriptor.samplerBindings = samplerBindings;

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
			std::string       byteCode = device->loadShaderByteCodeFromPath("Assets/Shaders/Triangle.slang");

			ShaderDescriptor vertexShaderDescriptor{};
			vertexShaderDescriptor.type = ShaderCodeType::eShaderSlang;
			vertexShaderDescriptor.data = byteCode;

			ShaderDescriptor fragmentShaderDescriptor{};
			fragmentShaderDescriptor.type = ShaderCodeType::eShaderSlang;
			vertexShaderDescriptor.data   = byteCode;

			std::shared_ptr<IShader> vertexShader   = device->createShader(vertexShaderDescriptor);
			std::shared_ptr<IShader> fragmentShader = device->createShader(vertexShaderDescriptor);

			fragmentShaderModule.shader     = fragmentShader;
			fragmentShaderModule.entryPoint = "fsmain";

			vertexShaderModule.shader     = vertexShader;
			vertexShaderModule.entryPoint = "vsmain";
		}

		std::vector<VertexInputLayout> vertexInputLayouts;
		{
			std::vector<VertexAttribute> vertexAttributes{
			    {VertexFormat::eFloat32x4, 0, 0},
			    {VertexFormat::eFloat32x2, 16, 0},
			};

			VertexInputLayout vertexInputLayout;
			vertexInputLayout.stepMode    = VertexStepMode::eVertex;
			vertexInputLayout.attributes  = vertexAttributes;
			vertexInputLayout.arrayStride = 24;
		}

		std::unique_ptr<IPipeline> pipeline;
		// pipeline creation
		{
			std::vector colorAttachment{TextureFormat::eRGBA32Float};

			RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
			rasterizerPipelineDescriptor.layout                 = layout;
			rasterizerPipelineDescriptor.vertexShaderModule     = vertexShaderModule;
			rasterizerPipelineDescriptor.fragmentShaderModule   = fragmentShaderModule;
			rasterizerPipelineDescriptor.inputLayouts           = vertexInputLayouts;
			rasterizerPipelineDescriptor.colorAttachmentFormats = colorAttachment;

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

		constexpr uint16_t MAX_INSTANCES_COUNT = 10000;

		struct InstanceData {
			std::array<float, 16> modelMatrix;
		};

		struct Vertex {
			std::array<float, 4> position;
			std::array<float, 2> uv;
		};

		std::shared_ptr<IBuffer>  instanceDatasBuffer;
		std::shared_ptr<IBuffer>  verticesBuffer;
		std::shared_ptr<ITexture> texture;
		std::shared_ptr<ISampler> sampler;
		// gpu resources creation
		{
			// instances data
			{
				BufferDescriptor bufferDescriptor{};
				bufferDescriptor.size  = sizeof(InstanceData) * MAX_INSTANCES_COUNT;
				bufferDescriptor.usage = BufferUsage::eStorage;

				instanceDatasBuffer = device->createBuffer(bufferDescriptor);
			}
			// vertices
			{
				BufferDescriptor bufferDescriptor{};
				bufferDescriptor.size  = sizeof(Vertex) * 3;
				bufferDescriptor.usage = BufferUsage::eVertex;

				verticesBuffer = device->createBuffer(bufferDescriptor);
			}
			// texture
			{
				TextureDescriptor textureDescriptor{};
				textureDescriptor.format      = TextureFormat::eRGBA32Float;
				textureDescriptor.memoryUsage = MemoryUsage::eGpu;
				textureDescriptor.usage       = TextureUsage::eSampled;

				texture = device->createTexture(textureDescriptor);
			}
			// sampler
			{
				SamplerDescriptor samplerDescriptor{};
				sampler = device->createSampler(samplerDescriptor);
			}
		}

		// resource views
		std::shared_ptr<ITextureView> textureView;
		std::shared_ptr<IBufferView>  vertexBufferView;
		std::shared_ptr<IBufferView>  instanceDataBufferBufferView;
		{
			TextureViewDescriptor textureViewDescriptor{};
			textureViewDescriptor.texture = texture;
			// cant we get these info from the texture this view is pointing
			textureViewDescriptor.format = TextureFormat::eRGBA32Float;
			textureViewDescriptor.usage  = TextureUsage::eSampled;

			textureView = device->createTextureView(textureViewDescriptor);

			BufferViewDescriptor bufferViewDescriptor{};
			bufferViewDescriptor.buffer = verticesBuffer;
			bufferViewDescriptor.usage  = BufferUsage::eVertex;
			bufferViewDescriptor.offset = 0;
			bufferViewDescriptor.size   = sizeof(Vertex) * 3;

			vertexBufferView = device->createBufferView(bufferViewDescriptor);

			BufferViewDescriptor instanceDataViewDescriptor{};
			instanceDataViewDescriptor.buffer = instanceDatasBuffer;
			instanceDataViewDescriptor.usage  = BufferUsage::eStorage;
			instanceDataViewDescriptor.offset = 0;
			instanceDataViewDescriptor.size   = sizeof(InstanceData) * MAX_INSTANCES_COUNT;
		}

		// Binding resources
		{
			resourceInputContainer->bindStorageBuffer(0, instanceDataBufferBufferView);
			resourceInputContainer->bindSampledTexture(1, textureView);

			samplerInputContainer->bindSampler(0, sampler);
		}

		std::unique_ptr<ICommandBuffer> commandBuffer;
		std::unique_ptr<ICommandAllocator> allocator;
		std::unique_ptr<ICommandQueue> queue;
		// commands
		{
			constexpr CommandAllocatorDescriptor descriptor{};
			allocator = device->createCommandAllocator(descriptor);
			constexpr CommandBufferDescriptor commandBufferDescriptor{};
			commandBuffer = allocator->allocateCommandBuffer(commandBufferDescriptor);
			CommandQueueDescriptor commandQueueDescriptor{};
			queue = device->createCommandQueue(commandQueueDescriptor);
		}

		// render one frame
		{
		}
	}

	INSTANTIATE_TEST_SUITE_P(
	    ApiChoice, RenderTest,
	    ::testing::Values("Vulkan", "Directx12"));
}  // namespace Synergon::Rhi
