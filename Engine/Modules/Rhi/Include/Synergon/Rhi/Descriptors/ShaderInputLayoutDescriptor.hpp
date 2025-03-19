#ifndef SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct ShaderResourceInputLayoutEntry {
		uint32_t                binding;
		ShaderStage::Type       stage;
		ShaderResourceInputType type;
	};

	struct ShaderResourceInputLayoutDescriptor {
		std::span<ShaderResourceInputLayoutEntry> resourceEntries;
	};

	struct ShaderSamplerInputLayoutDescriptor {
		std::span<uint32_t> samplerBindings;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP
