#ifndef SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP
#define SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP

namespace Synergon::Rhi {

	struct TextureDescriptor {
		uint32_t width{};
		uint32_t height{};
		uint32_t depth       = 1;
		uint32_t mipLevels   = 1;
		uint32_t arrayLayers = 1;
		uint32_t sampleCount = 1;

		TextureDimension		dimension{};
		TextureFormat			format{};

		TextureUsage::Type  	usage{};
		MemoryUsage   			memoryUsage{};
	};
}

#endif //#ifndef SYNERGON_RHI_TEXTUREDESCRIPTOR_HPP