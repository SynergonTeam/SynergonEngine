#ifndef SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP
#define SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct TextureViewDescriptor {
		TextureFormat      format;
		TextureUsage::Type usage;

		uint32_t baseMipLevel    = 0u;
		uint32_t mipLevelCount   = 1u;
		uint32_t baseArrayLayer  = 0u;
		uint32_t arrayLayerCount = 1u;

		TextureAspect::Type aspect    = TextureAspect::eColor;
		TextureDimension    dimension = TextureDimension::e2D;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP
