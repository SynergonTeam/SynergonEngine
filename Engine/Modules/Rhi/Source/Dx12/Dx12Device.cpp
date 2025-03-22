#include "Dx12Device.hpp"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace Synergon::Rhi {
	Dx12Device::Dx12Device() {}

	Dx12Device::~Dx12Device() {
		// Wait for all pending GPU operations to complete before destroying the device
		// *if i understand waitIdle() correctly
		try {
			waitIdle();
		} catch (const std::exception& e) {
			// Log the error but continue with destruction
			// We might want to use your engine's logging system
			OutputDebugStringA("Warning during Dx12Device destruction: Failed to wait for device idle state: ");
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

	void Dx12Device::waitIdle() const {
		throw std::logic_error("Not implemented yet");
	}

	void Dx12Device::waitForFences(std::span<std::shared_ptr<IFence>> fences) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IDisplay> Dx12Device::createDisplay(const DisplayDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBuffer> Dx12Device::createBuffer(const BufferDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITexture> Dx12Device::createTexture(const TextureDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ISampler> Dx12Device::createSampler(const SamplerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IBufferView> Dx12Device::createBufferView(const BufferViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<ITextureView> Dx12Device::createTextureView(const TextureViewDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandAllocator> Dx12Device::createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<ICommandQueue> Dx12Device::createCommandQueue(const CommandQueueDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShader> Dx12Device::createShader(const ShaderDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputPool> Dx12Device::createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> Dx12Device::createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputLayout> Dx12Device::createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IShaderInputContainer> Dx12Device::createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::shared_ptr<IPipelineLayout> Dx12Device::createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> Dx12Device::createComputePipeline(const ComputePipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IPipeline> Dx12Device::createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::unique_ptr<IFence> Dx12Device::createFence(const FenceDescriptor &descriptor) const {
		throw std::logic_error("Not implemented yet");
	}

	std::string Dx12Device::loadShaderByteCodeFromPath(std::string_view path) const {
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
			IDXGIAdapter1* pAdapter = nullptr;
			bool requestHighPerformanceAdapter = true;

			Microsoft::WRL::ComPtr<IDXGIFactory6> factory6;
			if (SUCCEEDED(factory->QueryInterface(IID_PPV_ARGS(&factory6)))) {
				for (
					UINT adapterIndex = 0;
					SUCCEEDED(factory6->EnumAdapterByGpuPreference(
						adapterIndex,
						requestHighPerformanceAdapter ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE
														: DXGI_GPU_PREFERENCE_UNSPECIFIED
														, IID_PPV_ARGS(&hardwareAdapter)));
					++adapterIndex)
				{
					DXGI_ADAPTER_DESC1 desc;
					hardwareAdapter->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
						// Don't select the Basic Render Driver adapter.
						continue;
					}

					// Check to see whether the adapter supports Direct3D 12, but don't create the
					// actual device yet.
					if (
						SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get()
								, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
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
					++adapterIndex)
				{
					DXGI_ADAPTER_DESC1 desc;
					hardwareAdapter->GetDesc1(&desc);

					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
						// Don't select the Basic Render Driver adapter.
						continue;
					}

					// Check to see whether the adapter supports Direct3D 12, but don't create the
					// actual device yet.
					if (
						SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get()
								, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
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
			IID_PPV_ARGS(&d3d12Device)
		));

		// Create and configure our device wrapper
		auto device = std::make_unique<Dx12Device>();
		device->m_Device = d3d12Device;

		return device;
	}

}  // namespace Synergon::Rhi
