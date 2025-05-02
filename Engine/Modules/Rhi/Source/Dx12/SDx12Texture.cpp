#include "SDx12Texture.hpp"

namespace Synergon::Rhi {

	SDx12Texture::SDx12Texture(const Microsoft::WRL::ComPtr<ID3D12Device>& device, const TextureDescriptor &descriptor) {
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
		// Miscellaneous flags that define additional properties of the resource.
		D3D12_HEAP_PROPERTIES heapProperties = {};
		heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
#endif

		SDx12Utils::ThrowIfFailed(device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&textureDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_Texture)));
	}

	TextureFormat SDx12Texture::getFormat() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return SDx12Utils::dxgiToTextureFormat(desc_.Format);
	}

	// TODO: Implement getMemoryUsage() to return the actual memory usage of the texture.
	MemoryUsage SDx12Texture::getMemoryUsage() const {
		return MemoryUsage();
	}

	// TODO: Implement getUsage() to return the actual usage of the texture.
	TextureUsage::Type SDx12Texture::getUsage() const {
		return TextureUsage::Type();
	}

	uint32_t SDx12Texture::getWidth() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return static_cast<uint32_t>(desc_.Width);
	}

	uint32_t SDx12Texture::getHeight() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return static_cast<uint32_t>(desc_.Height);
	}

	uint32_t SDx12Texture::getDepth() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return desc_.Dimension == D3D12_RESOURCE_DIMENSION_TEXTURE3D ?
			static_cast<uint32_t>(desc_.DepthOrArraySize) : 1;
	}

	uint32_t SDx12Texture::getMipLevels() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return static_cast<uint32_t>(desc_.MipLevels);
	}

	uint32_t SDx12Texture::getArrayLayers() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return desc_.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE3D ?
           static_cast<uint32_t>(desc_.DepthOrArraySize) : 1;
	}

	uint32_t SDx12Texture::getSampleCount() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return static_cast<uint32_t>(desc_.SampleDesc.Count);
	}

	TextureDimension SDx12Texture::getDimension() const {
		D3D12_TEXTURE_DESC(m_Texture);
		return SDx12Utils::dx12ToTextureDimension(desc_.Dimension);
	}

}  // namespace Synergon::Rhi
