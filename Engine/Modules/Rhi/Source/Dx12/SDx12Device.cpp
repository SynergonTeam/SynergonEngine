#include "SDx12Device.hpp"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace Synergon::Rhi {
	SDx12Device::SDx12Device() {}

	SDx12Device::~SDx12Device() {
		// Wait for all pending GPU operations to complete before destroying the device
		// *if i understand waitIdle() correctly
		try {
			waitIdle();
		} catch (const std::exception &e) {
			// Log the error but continue with destruction
			// We might want to use your engine's logging system
			OutputDebugStringA("Warning during SDx12Device destruction: Failed to wait for device idle state: ");
			OutputDebugStringA(e.what());
			OutputDebugStringA("\n");
		}

		// The ComPtr will automatically release the device when it goes out of scope,
		// but we can explicitly release it here for clarity
		if (m_Device) {
			// Report live objects in debug builds to catch resource leaks
#ifdef _DEBUG
			// Get the debug interface
			Microsoft::WRL::ComPtr<ID3D12DebugDevice> debugDevice;
			if (SUCCEEDED(m_Device.As(&debugDevice))) {
				// This will report any live objects through the debug layer
				debugDevice->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
			}
#endif

			m_Device.Reset();
		}

		// Any additional cleanup specific to your implementation can go here
	}

	void SDx12Device::waitIdle() const {
		throw std::logic_error("Not implemented yet");
	}

	void SDx12Device::waitForFences(std::span<std::shared_ptr<IFence>> fences) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IDisplay> SDx12Device::createDisplay(const DisplayDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBuffer> SDx12Device::createBuffer(const BufferDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITexture> SDx12Device::createTexture(const TextureDescriptor &descriptor) const {
		// Note: ComPtr's are CPU objects but this resource needs to stay in scope until
		// the command list that references it has finished executing on the GPU.
		// We will flush the GPU at the end of this method to ensure the resource is not
		// prematurely destroyed.
		Microsoft::WRL::ComPtr<ID3D12Resource> textureUploadHeap;

		// Create the texture.
		{
			// TODO: These two lambdas should probably be put into something like Utils.hpp or something like that.
			// To make it compatible between Vulkan, DirectX and our APIs
			const auto textureDimensionToDX12 = [](TextureDimension dim) -> D3D12_RESOURCE_DIMENSION {
				switch (dim) {
					case TextureDimension::e1D:   return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
					case TextureDimension::e2D:   return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
					case TextureDimension::e3D:   return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
					case TextureDimension::eCube: return D3D12_RESOURCE_DIMENSION_TEXTURE2D; // Cubes are 2D textures in DX12?
					default:                      return D3D12_RESOURCE_DIMENSION_UNKNOWN;
				}
			};

			const auto textureFormatToDXGI = [](TextureFormat format) -> DXGI_FORMAT {
				switch (format) {
					case TextureFormat::eR8Unorm:              return DXGI_FORMAT_R8_UNORM;
					case TextureFormat::eR8Snorm:              return DXGI_FORMAT_R8_SNORM;
					case TextureFormat::eR8Uint:               return DXGI_FORMAT_R8_UINT;
					case TextureFormat::eR8Sint:               return DXGI_FORMAT_R8_SINT;
					case TextureFormat::eR16Unorm:             return DXGI_FORMAT_R16_UNORM;
					case TextureFormat::eR16Snorm:             return DXGI_FORMAT_R16_SNORM;
					case TextureFormat::eR16Uint:              return DXGI_FORMAT_R16_UINT;
					case TextureFormat::eR16Sint:              return DXGI_FORMAT_R16_SINT;
					case TextureFormat::eR16Float:             return DXGI_FORMAT_R16_FLOAT;
					case TextureFormat::eR32Uint:              return DXGI_FORMAT_R32_UINT;
					case TextureFormat::eR32Sint:              return DXGI_FORMAT_R32_SINT;
					case TextureFormat::eR32Float:             return DXGI_FORMAT_R32_FLOAT;
					case TextureFormat::eRG8Unorm:             return DXGI_FORMAT_R8G8_UNORM;
					case TextureFormat::eRG8Snorm:             return DXGI_FORMAT_R8G8_SNORM;
					case TextureFormat::eRG8Uint:              return DXGI_FORMAT_R8G8_UINT;
					case TextureFormat::eRG8Sint:              return DXGI_FORMAT_R8G8_SINT;
					case TextureFormat::eRG16Unorm:            return DXGI_FORMAT_R16G16_UNORM;
					case TextureFormat::eRG16Snorm:            return DXGI_FORMAT_R16G16_SNORM;
					case TextureFormat::eRG16Uint:             return DXGI_FORMAT_R16G16_UINT;
					case TextureFormat::eRG16Sint:             return DXGI_FORMAT_R16G16_SINT;
					case TextureFormat::eRG16Float:            return DXGI_FORMAT_R16G16_FLOAT;
					case TextureFormat::eRG32Uint:             return DXGI_FORMAT_R32G32_UINT;
					case TextureFormat::eRG32Sint:             return DXGI_FORMAT_R32G32_SINT;
					case TextureFormat::eRG32Float:            return DXGI_FORMAT_R32G32_FLOAT;
					case TextureFormat::eRGB8Unorm:            return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB8Snorm:            return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB8Uint:             return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB8Sint:             return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB16Unorm:           return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB16Snorm:           return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB16Uint:            return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB16Sint:            return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB16Float:           return DXGI_FORMAT_UNKNOWN;
					case TextureFormat::eRGB32Uint:            return DXGI_FORMAT_R32G32B32_UINT;
					case TextureFormat::eRGB32Sint:            return DXGI_FORMAT_R32G32B32_SINT;
					case TextureFormat::eRGB32Float:           return DXGI_FORMAT_R32G32B32_FLOAT;
					case TextureFormat::eRGBA8Unorm:           return DXGI_FORMAT_R8G8B8A8_UNORM;
					case TextureFormat::eRGBA8Snorm:           return DXGI_FORMAT_R8G8B8A8_SNORM;
					case TextureFormat::eRGBA8Uint:            return DXGI_FORMAT_R8G8B8A8_UINT;
					case TextureFormat::eRGBA8Sint:            return DXGI_FORMAT_R8G8B8A8_SINT;
					case TextureFormat::eRGBA16Unorm:          return DXGI_FORMAT_R16G16B16A16_UNORM;
					case TextureFormat::eRGBA16Snorm:          return DXGI_FORMAT_R16G16B16A16_SNORM;
					case TextureFormat::eRGBA16Uint:           return DXGI_FORMAT_R16G16B16A16_UINT;
					case TextureFormat::eRGBA16Sint:           return DXGI_FORMAT_R16G16B16A16_SINT;
					case TextureFormat::eRGBA16Float:          return DXGI_FORMAT_R16G16B16A16_FLOAT;
					case TextureFormat::eRGBA32Uint:           return DXGI_FORMAT_R32G32B32A32_UINT;
					case TextureFormat::eRGBA32Sint:           return DXGI_FORMAT_R32G32B32A32_SINT;
					case TextureFormat::eRGBA32Float:          return DXGI_FORMAT_R32G32B32A32_FLOAT;
					case TextureFormat::eDepth16Unorm:         return DXGI_FORMAT_D16_UNORM;
					case TextureFormat::eDepth24Unorm:         return DXGI_FORMAT_UNKNOWN; // or D24_UNORM_S8_UINT?
					case TextureFormat::eDepth32Float:         return DXGI_FORMAT_D32_FLOAT;
					case TextureFormat::eDepth24Stencil8:      return DXGI_FORMAT_D24_UNORM_S8_UINT;
					case TextureFormat::eDepth32FloatStencil8: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
					default:                                   return DXGI_FORMAT_UNKNOWN;
				}
			};

			// Describe and create a Texture2D.
			D3D12_RESOURCE_DESC textureDesc = {};

			// Number of detail levels (mip levels) of the texture.
			// Used to store the texture at different resolutions for optimized rendering at various distances.
			textureDesc.MipLevels = descriptor.mipLevels;

			// Pixel format of the texture (e.g., R8G8B8A8_UNORM, R32G32B32A32_FLOAT, etc.).
			// Defines how the data will be stored and interpreted by the graphics processor.
			textureDesc.Format = textureFormatToDXGI(descriptor.format);

			// Width of the texture in pixels.
			textureDesc.Width = descriptor.width;

			// Height of the texture in pixels.
			textureDesc.Height = descriptor.height;

			// Resource flags that define additional properties (e.g., support for rendering to texture).
			// D3D12_RESOURCE_FLAG_NONE means no special properties are required.
			textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			// For 3D textures - depth in pixels. For texture arrays - number of textures in the array.
			textureDesc.DepthOrArraySize = descriptor.depth;

			// Multisampling settings for edge smoothing.
			// Count - number of samples per pixel (1 means no multisampling).
			textureDesc.SampleDesc.Count = descriptor.sampleCount;

			// Quality level of multisampling (usually 0 for standard quality).
			textureDesc.SampleDesc.Quality = 0;

			// Type of texture (1D, 2D, 3D, or cube).
			// Defines the dimensionality and how the texture is accessed in shaders.
			textureDesc.Dimension = textureDimensionToDX12(descriptor.dimension);

			ThrowIfFailed(m_Device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&textureDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&m_texture)));

			const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_texture.Get(), 0, 1);

			// Create the GPU upload buffer.
			ThrowIfFailed(m_Device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&textureUploadHeap)));

			// Copy data to the intermediate upload heap and then schedule a copy
			// from the upload heap to the Texture2D.
			std::vector<UINT8> texture = GenerateTextureData();

			D3D12_SUBRESOURCE_DATA textureData = {};
			textureData.pData = &texture[0];
			textureData.RowPitch = TextureWidth * TexturePixelSize;
			textureData.SlicePitch = textureData.RowPitch * TextureHeight;

			UpdateSubresources(m_commandList.Get(), m_texture.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
			m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

			// Describe and create a SRV for the texture.
			D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvDesc.Format = textureDesc.Format;
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = 1;
			m_Device->CreateShaderResourceView(m_texture.Get(), &srvDesc, m_srvHeap->GetCPUDescriptorHandleForHeapStart());
		}
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ISampler> SDx12Device::createSampler(const SamplerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBufferView> SDx12Device::createBufferView(const BufferViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITextureView> SDx12Device::createTextureView(const TextureViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ICommandAllocator> SDx12Device::createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandQueue> SDx12Device::createCommandQueue(const CommandQueueDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShader> SDx12Device::createShader(const ShaderDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputPool> SDx12Device::createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> SDx12Device::createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> SDx12Device::createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputContainer> SDx12Device::createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipelineLayout> SDx12Device::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipeline> SDx12Device::createComputePipeline(const ComputePipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipeline> SDx12Device::createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IFence> SDx12Device::createFence(const FenceDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::string SDx12Device::loadShaderByteCodeFromPath(std::string_view path) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IDevice> CreateDx12Device() {
		UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
		// Enable the debug layer (requires the Graphics Tools "optional feature").
		// NOTE: Enabling the debug layer after device creation will invalidate the active device.
		{
			Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
				debugController->EnableDebugLayer();

				// Enable additional debug layers.
				dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}
#endif

		// Create DXGI factory
		Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
		ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

		// Find hardware adapter
		Microsoft::WRL::ComPtr<IDXGIAdapter1> hardwareAdapter;

		// Inline adapter finding logic
		{
			IDXGIAdapter1 *pAdapter                      = nullptr;
			bool           requestHighPerformanceAdapter = true;

			Microsoft::WRL::ComPtr<IDXGIFactory6> factory6;
			if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(&factory6)))) {
				for (
				    UINT adapterIndex = 0;
				    SUCCEEDED(factory6->EnumAdapterByGpuPreference(
				        adapterIndex,
				        requestHighPerformanceAdapter ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE
				                                      : DXGI_GPU_PREFERENCE_UNSPECIFIED,
				        IID_PPV_ARGS(&hardwareAdapter)));
				    ++adapterIndex) {
					DXGI_ADAPTER_DESC1 desc;
					hardwareAdapter->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
						// Don't select the Basic Render Driver adapter.
						continue;
					}

					// Check to see whether the adapter supports Direct3D 12, but don't create the
					// actual device yet.
					//! "'_uuidof' was not declared in this scope", thus changed to __uuidof
					//! and also, __uuidof need <initguid.h> header
					if (
					    SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
						break;
					}

					hardwareAdapter = nullptr;
				}
			}

			// Fallback to original enumeration method
			if (hardwareAdapter.Get() == nullptr) {
				for (
				    UINT adapterIndex = 0;
				    SUCCEEDED(factory->EnumAdapters1(adapterIndex, &hardwareAdapter));
				    ++adapterIndex) {
					DXGI_ADAPTER_DESC1 desc;
					hardwareAdapter->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
						// Don't select the Basic Render Driver adapter.
						continue;
					}

					// Check to see whether the adapter supports Direct3D 12, but don't create the
					// actual device yet.
					//! "'_uuidof' was not declared in this scope", thus changed to __uuidof
					//! and also, __uuidof need <initguid.h> header
					if (
					    SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr))) {
						break;
					}

					hardwareAdapter = nullptr;
				}
			}
		}

		if (hardwareAdapter.Get() == nullptr) {
			throw std::runtime_error("Failed to find a suitable DirectX 12 adapter");
		}

		// Create D3D12 device
		Microsoft::WRL::ComPtr<ID3D12Device> d3d12Device;
		ThrowIfFailed(D3D12CreateDevice(
		    hardwareAdapter.Get(),
		    D3D_FEATURE_LEVEL_11_0,
		    IID_PPV_ARGS(&d3d12Device)));

		// Create and configure our device wrapper
		auto device = std::make_unique<SDx12Device>();
		device->setDevice(d3d12Device);

		return device;
	}

}  // namespace Synergon::Rhi
