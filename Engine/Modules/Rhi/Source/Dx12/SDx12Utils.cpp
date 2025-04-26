
#include "SDx12Utils.hpp"

namespace Synergon::Rhi {

	D3D12_RESOURCE_DIMENSION SDx12Utils::textureDimensionToDX12(TextureDimension dim) {
		switch (dim) {
			case TextureDimension::e1D:   return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
			case TextureDimension::e2D:   return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			case TextureDimension::e3D:   return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
			case TextureDimension::eCube: return D3D12_RESOURCE_DIMENSION_TEXTURE2D; // Cubes are 2D textures in DX12
			default:                      return D3D12_RESOURCE_DIMENSION_UNKNOWN;
		}
	}

	DXGI_FORMAT SDx12Utils::textureFormatToDXGI(TextureFormat format) {
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
	}

} // namespace Synergon::Rhi