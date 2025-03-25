#pragma once

#include "Synergon/Rhi/IDevice.hpp"

// Maybe do something like stdafx.h from the DirectX-Graphics-Samples repository on GitHub
// link: https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HelloWorld/src/HelloTriangle
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <stdexcept>

namespace Synergon::Rhi {

	// This class and function is taken from the DirectX-Graphics-Samples repository on GitHub,
	// found it very useful for error handling, but we need to do something like DXSampleHelper
	// link: https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HelloWorld/src/HelloTriangle
	/************************************************************************************/
	inline std::string HrToString(HRESULT hr) {
		char s_str[64] = {};
		sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
		return std::string(s_str);
	}

	class HrException : public std::runtime_error {
	public:
		HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
		HRESULT Error() const { return m_hr; }
	private:
		const HRESULT m_hr;
	};

	inline void ThrowIfFailed(HRESULT hr) {
		if (FAILED(hr)) {
			throw HrException(hr);
		}
	}
	/************************************************************************************/

	/**
	 * @brief A DirectX 12 implementation of the engine's device interface.
	 *
	 * This class wraps the DirectX 12 device and provides the implementation for the engine's device
	 * interface. It is responsible for creating all other DirectX 12 resources and managing their
	 * lifetimes.
	 *
	 * @note This class is not intended to be used directly, but through the engine's device factory
	 *       function CreateDx12Device.
	 */
	class Dx12Device final : public IDevice {
	public:
		Dx12Device();
		~Dx12Device() override;
		Dx12Device(const Dx12Device& other) = delete;
		Dx12Device& operator=(const Dx12Device& other) = delete;
		Dx12Device(Dx12Device &&other) noexcept        = delete;
		Dx12Device &operator=(Dx12Device &&other) noexcept = delete;

		void waitIdle() const override;
		void waitForFences(std::span<std::shared_ptr<IFence>> fences) const override;

		std::unique_ptr<IDisplay> createDisplay(const DisplayDescriptor &descriptor) const override;

		std::shared_ptr<IBuffer>  createBuffer(const BufferDescriptor &descriptor) const override;
		std::shared_ptr<ITexture> createTexture(const TextureDescriptor &descriptor) const override;
		std::shared_ptr<ISampler> createSampler(const SamplerDescriptor &descriptor) const override;

		std::shared_ptr<IBufferView>  createBufferView(const BufferViewDescriptor &descriptor) const override;
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor &descriptor) const override;

		std::unique_ptr<ICommandAllocator> createCommandAllocator(const CommandAllocatorDescriptor &descriptor) const override;
		std::unique_ptr<ICommandQueue>     createCommandQueue(const CommandQueueDescriptor &descriptor) const override;

		std::shared_ptr<IShader> createShader(const ShaderDescriptor &descriptor) const override;

		std::shared_ptr<IShaderInputPool>      createShaderInputPool(const ShaderInputPoolDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderResourceInputLayoutDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputLayout>    createShaderInputLayout(const ShaderSamplerInputLayoutDescriptor &descriptor) const override;
		std::shared_ptr<IShaderInputContainer> createShaderInputContainer(const ShaderInputContainerDescriptor &descriptor) const override;

		std::shared_ptr<IPipelineLayout> createPipelineLayout(const PipelineLayoutDescriptor &descriptor) const override;
		std::unique_ptr<IPipeline>       createComputePipeline(const ComputePipelineDescriptor &descriptor) const override;
		std::unique_ptr<IPipeline>       createRasterizerPipeline(const RasterizerPipelineDescriptor &descriptor) const override;

		std::unique_ptr<IFence> createFence(const FenceDescriptor &descriptor) const override;

		std::string loadShaderByteCodeFromPath(std::string_view path) const override;

		inline Microsoft::WRL::ComPtr<ID3D12Device> getDevice() const { return m_Device; }
		inline ID3D12Device *getDeviceRaw() const { return m_Device.Get(); }

		inline void setDevice(Microsoft::WRL::ComPtr<ID3D12Device> device) { m_Device = device; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Device> m_Device;

	};

	/**
	 * @brief Creates a DirectX 12 device wrapped in the engine's device interface.
	 *
	 * This function performs the complete initialization process for a DirectX 12 device:
	 * 1. Enables debug layers if in debug mode
	 * 2. Creates a DXGI factory
	 * 3. Finds a suitable hardware adapter (GPU) with DirectX 12 support
	 * 4. Creates the actual DirectX 12 device
	 * 5. Wraps it in the engine's device interface
	 *
	 * The function first attempts to find a high-performance adapter using IDXGIFactory6 interface
	 * if available. If that fails, it falls back to the standard adapter enumeration method.
	 * Software adapters (like the Basic Render Driver) are explicitly excluded from selection.
	 *
	 * @throws HrException If any DirectX API call fails (via ThrowIfFailed)
	 * @throws std::runtime_error If no suitable DirectX 12 adapter can be found
	 *
	 * @return std::unique_ptr<IDevice> A unique pointer to the created device, encapsulating
	 *                                 the DirectX 12 implementation details
	 *
	 * @note This function requires dxgi.lib and d3d12.lib to be linked to the project
	 * @note The device is created with feature level D3D_FEATURE_LEVEL_11_0 as the minimum requirement
	 * @note In debug builds, the DirectX 12 debug layer is enabled for enhanced error reporting
	 * @note Device creation taken from the microsoft/DirectX-Graphics-Samples repository on GitHub
	 * link: https://github.com/microsoft/DirectX-Graphics-Samples/
	 */
	std::unique_ptr<IDevice> CreateDx12Device();

}  // namespace Synergon::Rhi
