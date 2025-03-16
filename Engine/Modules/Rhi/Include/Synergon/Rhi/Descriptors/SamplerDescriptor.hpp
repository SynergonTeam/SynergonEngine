#ifndef SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP
#define SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct SamplerDescriptor {
		AddressMode addressModeU{};
		AddressMode addressModeV{};
		AddressMode addressModeW{};

		Filter minFilter{};
		Filter magFilter{};
		Filter mipMapFilter{};

		CompareOp compareOp{};

		float    lodMinClamp   = 0.0f;
		float    lodMaxClamp   = 32.0f;
		uint16_t maxAnisotropy = 1;
	};
}

#endif //SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP
