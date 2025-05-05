#pragma once

#include <wrl.h>
#include <d3d12.h>
#include "SDx12Utils.hpp"
#include "Synergon/Rhi/Descriptors/TextureDescriptor.hpp"

#include <memory>

#define D3D12_TEXTURE_DESC(d3d12_texture) \
	D3D12_RESOURCE_DESC desc_ = {};       \
	if (d3d12_texture) {                  \
		desc_ = d3d12_texture->GetDesc(); \
	}

namespace Synergon::Rhi {

	/**
	 * @brief DirectX 12 texture class
	 *
	 * This class encapsulates a DirectX 12 texture resource and provides methods for
	 * creating and managing textures in the DirectX 12 API.
	 */
	class SDx12Texture : public ITexture {

	public:
		SDx12Texture(const Microsoft::WRL::ComPtr<ID3D12Device>& device, const TextureDescriptor& descriptor);

		TextureFormat      getFormat() const override;
		MemoryUsage        getMemoryUsage() const override;
		TextureUsage::Type getUsage() const override;

		uint32_t getWidth() const override;
		uint32_t getHeight() const override;

		uint32_t getDepth() const override;
		uint32_t getMipLevels() const override;
		uint32_t getArrayLayers() const override;
		uint32_t getSampleCount() const override;

		TextureDimension getDimension() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_Texture;
	};


}  // namespace Synergon::Rhi
