#ifndef SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP

namespace Synergon::Rhi {
	struct ShaderInputLayoutEntry {
		uint32_t              binding;
		ShaderStage::Type     stage;
		ShaderInputType::Type type;
	};

	struct ShaderInputLayoutDescriptor {
		std::span<ShaderInputLayoutEntry> resourceEntries;
		std::span<uint32_t>               samplerBindings;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_SHADERINPUTLAYOUTDESCRIPTOR_HPP
