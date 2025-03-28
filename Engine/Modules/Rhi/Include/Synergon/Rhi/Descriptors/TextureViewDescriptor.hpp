#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include "Synergon/Rhi/IShaderInputPool.hpp"
#include "Synergon/Rhi/ITexture.hpp"

#include <memory>
#include <cstdint>

namespace Synergon::Rhi {
	struct TextureViewDescriptor {
		std::shared_ptr<IShaderInputPool> pool;
		std::shared_ptr<ITexture>         texture;

		TextureFormat      format;
		TextureUsage::Type usage;

		uint32_t baseMipLevel    = 0u;
		uint32_t mipLevelCount   = 1u;
		uint32_t baseArrayLayer  = 0u;
		uint32_t arrayLayerCount = 1u;

		TextureAspect::Type  aspect    = TextureAspect::eColor;
		TextureViewDimension dimension = TextureViewDimension::e2D;
	};
}  // namespace Synergon::Rhi
