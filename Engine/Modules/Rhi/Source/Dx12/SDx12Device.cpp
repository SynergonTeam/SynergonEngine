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
		// Describe and create a Texture2D.
		D3D12_RESOURCE_DESC textureDesc = {};

		// Type of texture (1D, 2D, 3D, or cube).
		// Defines the dimensionality and how the texture is accessed in shaders.
		textureDesc.Dimension = SDx12Utils::textureDimensionToDX12(descriptor.dimension);

		// Alignment of the texture data in memory.
		// Alignment may be one of 0, 4KB, 64KB or 4MB.
		// If Alignment is set to 0, the runtime will use 4MB for MSAA textures and 64KB for everything else.
		// The application may choose smaller alignments than these defaults for a couple of texture types
		// when the texture is small. Textures with UNKNOWN layout and MSAA may be created with
		// 64KB alignment.
		textureDesc.Alignment = 0;

		// Width of the texture in pixels.
		textureDesc.Width = descriptor.width;

		// Height of the texture in pixels.
		textureDesc.Height = descriptor.height;

		// For 3D textures - depth in pixels. For texture arrays - number of textures in the array.
		textureDesc.DepthOrArraySize = descriptor.depth;

		// Number of detail levels (mip levels) of the texture.
		// Used to store the texture at different resolutions for optimized rendering at various distances.
		textureDesc.MipLevels = descriptor.mipLevels;

		// Pixel format of the texture (e.g., R8G8B8A8_UNORM, R32G32B32A32_FLOAT, etc.).
		// Defines how the data will be stored and interpreted by the graphics processor.
		textureDesc.Format = SDx12Utils::textureFormatToDXGI(descriptor.format);

		// Multisampling settings for edge smoothing.
		// Count - number of samples per pixel (1 means no multisampling).
		textureDesc.SampleDesc.Count = descriptor.sampleCount;

		// Quality level of multisampling (usually 0 for standard quality).
		textureDesc.SampleDesc.Quality = 0;

		// Layout of the texture data in memory.
		// D3D12_TEXTURE_LAYOUT_UNKNOWN means let driver optimize it for GPU.
		// or use D3D12_TEXTURE_LAYOUT_ROW_MAJOR?
		textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		// Resource flags that define additional properties (e.g., support for rendering to texture).
		// D3D12_RESOURCE_FLAG_NONE means no special properties are required.
		textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
#if 0
		SDx12Utils::ThrowIfFailed(m_Device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&textureDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_Texture)));
#endif
		return nullptr;
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
		SDx12Utils::ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

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
		SDx12Utils::ThrowIfFailed(D3D12CreateDevice(
		    hardwareAdapter.Get(),
		    D3D_FEATURE_LEVEL_11_0,
		    IID_PPV_ARGS(&d3d12Device)));

		// Create and configure our device wrapper
		auto device = std::make_unique<SDx12Device>();
		device->setDevice(d3d12Device);

		return device;
	}

}  // namespace Synergon::Rhi
