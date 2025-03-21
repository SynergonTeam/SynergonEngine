#pragma once

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/ITexture.hpp"

namespace Synergon::Rhi {
	class ITextureView {
	   public:
		virtual ~ITextureView() = default;

		virtual std::shared_ptr<ITexture>         getTexture() const   = 0;

		virtual TextureFormat      getFormat() const = 0;
		virtual TextureUsage::Type getUsage() const  = 0;

		virtual uint32_t getBaseMipLevel() const    = 0;
		virtual uint32_t getMipLevelCount() const   = 0;
		virtual uint32_t getBaseArrayLayer() const  = 0;
		virtual uint32_t getArrayLayerCount() const = 0;

		virtual TextureAspect::Type getAspect() const    = 0;
		virtual TextureDimension    getDimension() const = 0;
	};
}  // namespace Synergon::Rhi
