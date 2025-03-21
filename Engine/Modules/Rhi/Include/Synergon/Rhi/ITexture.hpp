#ifndef SYNERGON_RHI_ITEXTURE_HPP
#define SYNERGON_RHI_ITEXTURE_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	class ITexture {
	   public:
		virtual ~ITexture() = default;

		virtual TextureFormat      getFormat() const      = 0;
		virtual MemoryUsage        getMemoryUsage() const = 0;
		virtual TextureUsage::Type getUsage() const       = 0;

		virtual uint32_t getWidth() const  = 0;
		virtual uint32_t getHeight() const = 0;

		virtual uint32_t getDepth() const       = 0;
		virtual uint32_t getMipLevels() const   = 0;
		virtual uint32_t getArrayLayers() const = 0;
		virtual uint32_t getSampleCount() const = 0;

		virtual TextureDimension getDimension() const = 0;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_ITEXTURE_HPP