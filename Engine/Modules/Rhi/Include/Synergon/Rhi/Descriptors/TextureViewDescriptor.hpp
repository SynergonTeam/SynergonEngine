#ifndef SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP
#define SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct TextureViewDescriptor {
		TextureDimension dimension;
		TextureFormat    format;

		TextureUsage::Type     usage;
		TextureAspect::Type    aspect;

		uint32_t baseMipLevel    = 0u;
		uint32_t mipLevelCount   = 1u;
		uint32_t baseArrayLayer  = 0u;
		uint32_t arrayLayerCount = 1u;
	};
}

#endif //SYNERGON_RHI_TEXTUREVIEWDESCRIPTOR_HPP
