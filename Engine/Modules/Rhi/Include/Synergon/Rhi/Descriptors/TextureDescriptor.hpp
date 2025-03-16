#ifndef SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP
#define SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP

namespace Synergon::Rhi {

	struct TextureDescriptor {
		TextureFormat      format;
		MemoryUsage        memoryUsage;
		TextureUsage::Type usage;

		uint32_t width;
		uint32_t height;

		uint32_t depth       = 1u;
		uint32_t mipLevels   = 1u;
		uint32_t arrayLayers = 1u;
		uint32_t sampleCount = 1u;

		TextureDimension dimension = TextureDimension::e2D;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP