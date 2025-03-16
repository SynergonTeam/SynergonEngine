#ifndef SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP
#define SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct SamplerDescriptor {
		AddressMode addressModeU = AddressMode::eRepeat;
		AddressMode addressModeV = AddressMode::eRepeat;
		AddressMode addressModeW = AddressMode::eRepeat;

		Filter minFilter    = Filter::eLinear;
		Filter magFilter    = Filter::eLinear;
		Filter mipMapFilter = Filter::eLinear;

		CompareOp compareOp = CompareOp::eNever;

		float    lodMinClamp   = 0.0f;
		float    lodMaxClamp   = 32.0f;
		uint16_t maxAnisotropy = 1u;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_SAMPLERDESCRIPTOR_HPP
