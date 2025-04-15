#include "SimpleTriangleRenderTest.hpp"

#include "Utils.hpp"

#include "Synergon/Core/FileHelpers.hpp"

#include <array>

namespace Synergon::Rhi {
	void SimpleTriangleRenderTest::init() {
		const std::string apiName = GetParam();
		m_Device                  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		// display creation
		std::unique_ptr<IDisplay> display;
		{
			DisplayDescriptor displayDescriptor;
			displayDescriptor.windowHandle = nullptr;

			m_Display = m_Device->createDisplay(displayDescriptor);
		}

		std::shared_ptr<IPipelineLayout>    layout;
		std::shared_ptr<IShaderInputLayout> sceneSamplerInputLayout;
		std::shared_ptr<IShaderInputLayout> sceneDataResourcesInputLayout;
		// layout
		{
			// scene data layout
			{
				ShaderResourceInputLayoutDescriptor shaderInputLayoutDescriptor;

				std::vector<ShaderResourceInputLayoutEntry> resourceEntries = {
				    {0, ShaderStage::eFragment, ShaderResourceInputType::eSampledTexture},  // texture
				};

				shaderInputLayoutDescriptor.resourceEntries = resourceEntries;
				sceneDataResourcesInputLayout               = m_Device->createShaderInputLayout(shaderInputLayoutDescriptor);
			}

			{
				std::vector<uint32_t> samplerBindings = {0};

				ShaderSamplerInputLayoutDescriptor samplerInputLayoutDescriptor;
				samplerInputLayoutDescriptor.samplerBindings = samplerBindings;

				// todo: I really think that we should directly pass vector of sampler bindings, users won't like this
				sceneSamplerInputLayout = m_Device->createShaderInputLayout(samplerInputLayoutDescriptor);
			}

			// pipeline layout creation
			{
				std::vector shaderInputLayouts{
				    sceneDataResourcesInputLayout,
				    sceneSamplerInputLayout};

				PipelineLayoutDescriptor pipelineLayoutDescriptor;
				pipelineLayoutDescriptor.shaderInputLayouts = shaderInputLayouts;
				pipelineLayoutDescriptor.pushConstantRanges = {};

				layout = m_Device->createPipelineLayout(pipelineLayoutDescriptor);
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

			std::shared_ptr<IShader> vertexShader   = m_Device->createShader(vertexShaderDescriptor);
			std::shared_ptr<IShader> fragmentShader = m_Device->createShader(vertexShaderDescriptor);

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
			vertexInputLayout.attributes  = vertexAttributes;
			vertexInputLayout.arrayStride = 24;
		}

		// pipeline creation
		{
			RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
			rasterizerPipelineDescriptor.layout               = layout;
			rasterizerPipelineDescriptor.vertexShaderModule   = vertexShaderModule;
			rasterizerPipelineDescriptor.fragmentShaderModule = fragmentShaderModule;
			rasterizerPipelineDescriptor.inputLayouts         = vertexInputLayouts;

			EXPECT_NO_THROW(m_Pipeline = m_Device->createRasterizerPipeline(rasterizerPipelineDescriptor));
		}

		std::shared_ptr<IShaderInputPool> resourceShaderInputPool;
		{
			ShaderInputPoolDescriptor shaderInputPoolDesc{};
			shaderInputPoolDesc.type  = ShaderInputType::eResource;
			shaderInputPoolDesc.count = 100;

			EXPECT_NO_THROW(resourceShaderInputPool = m_Device->createShaderInputPool(shaderInputPoolDesc));
		}

		std::shared_ptr<IShaderInputPool> samplerShaderInputPool;
		{
			ShaderInputPoolDescriptor shaderInputPoolDesc{};
			shaderInputPoolDesc.type  = ShaderInputType::eSampler;
			shaderInputPoolDesc.count = 100;

			EXPECT_NO_THROW(samplerShaderInputPool = m_Device->createShaderInputPool(shaderInputPoolDesc));
		}

		// resource input container
		{
			ShaderInputContainerDescriptor resourceInputContainerDescriptor;
			resourceInputContainerDescriptor.layout = sceneDataResourcesInputLayout;
			resourceInputContainerDescriptor.pool   = resourceShaderInputPool;

			EXPECT_NO_THROW(m_ResourceInputContainer = m_Device->createShaderInputContainer(resourceInputContainerDescriptor));
		}

		// sampler input container
		{
			ShaderInputContainerDescriptor resourceInputContainerDescriptor;
			resourceInputContainerDescriptor.layout = sceneSamplerInputLayout;
			resourceInputContainerDescriptor.pool   = samplerShaderInputPool;

			EXPECT_NO_THROW(m_SamplerInputContainer = m_Device->createShaderInputContainer(resourceInputContainerDescriptor));
		}

		struct Vertex {
			std::array<float, 4> position;
			std::array<float, 2> uv;
		};

		// resources
		std::shared_ptr<IBuffer> vertexBuffer;
		{
			BufferDescriptor vertexBufferDesc{};

			vertexBufferDesc.size        = sizeof(Vertex) * 3;
			vertexBufferDesc.usage       = BufferUsage::eVertex;
			vertexBufferDesc.memoryUsage = MemoryUsage::eGpu;

			EXPECT_NO_THROW(vertexBuffer = m_Device->createBuffer(vertexBufferDesc));
		}

		std::shared_ptr<ITexture> triangleTexture;
		{
			TextureDescriptor textureDescriptor{};

			textureDescriptor.format      = TextureFormat::eRGB32Float;
			textureDescriptor.memoryUsage = MemoryUsage::eGpu;
			textureDescriptor.usage       = TextureUsage::eSampled;

			textureDescriptor.width  = 32;
			textureDescriptor.height = 32;
			textureDescriptor.depth  = 1;

			EXPECT_NO_THROW(triangleTexture = m_Device->createTexture(textureDescriptor));
		}

		std::shared_ptr<ISampler> sampler;
		{
			constexpr SamplerDescriptor descriptor{};
			EXPECT_NO_THROW(sampler = m_Device->createSampler(descriptor));
		}

		{
			BufferViewDescriptor bufferViewDesc{};

			bufferViewDesc.inputPool = resourceShaderInputPool;
			bufferViewDesc.buffer    = vertexBuffer;

			bufferViewDesc.usage  = vertexBuffer->getUsage();
			bufferViewDesc.offset = 0;
			bufferViewDesc.size   = vertexBuffer->getSize();

			EXPECT_NO_THROW(m_VertexBufferView = m_Device->createBufferView(bufferViewDesc));
		}

		{
			TextureViewDescriptor textureViewDesc{};

			textureViewDesc.pool    = resourceShaderInputPool;
			textureViewDesc.texture = triangleTexture;

			textureViewDesc.format = triangleTexture->getFormat();
			textureViewDesc.usage  = triangleTexture->getUsage();

			EXPECT_NO_THROW(m_TriangleTextureView = m_Device->createTextureView(textureViewDesc));
		}

		{
			ShaderInputContainerDescriptor shaderInputContainerDescriptor{};
			shaderInputContainerDescriptor.layout = sceneDataResourcesInputLayout;
			shaderInputContainerDescriptor.pool   = resourceShaderInputPool;

			EXPECT_NO_THROW(m_ShaderResourceInputContainer = m_Device->createShaderInputContainer(shaderInputContainerDescriptor));
		}

		{
			ShaderInputContainerDescriptor shaderInputContainerDescriptor{};
			shaderInputContainerDescriptor.layout = sceneSamplerInputLayout;
			shaderInputContainerDescriptor.pool   = samplerShaderInputPool;

			EXPECT_NO_THROW(m_ShaderSamplerInputContainer = m_Device->createShaderInputContainer(shaderInputContainerDescriptor));
		}

		{
			EXPECT_NO_THROW(m_ShaderResourceInputContainer->bindSampledTexture(0, m_TriangleTextureView));
			EXPECT_NO_THROW(m_ShaderSamplerInputContainer->bindSampler(0, sampler));
		}
	}

	TEST_P(SimpleTriangleRenderTest, DefaultConstruction) {
		init();
	}
}  // namespace Synergon::Rhi
