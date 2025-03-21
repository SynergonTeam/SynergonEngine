#ifndef SYNERGON_RHI_SHADERDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERDESCRIPTOR_HPP

#include <cstdint>
#include <string>

namespace Synergon::Rhi {

	enum class ShaderCodeType {
		eShaderSlang,
		eNativeByteCode,
	};

	struct ShaderDescriptor {
		ShaderCodeType type = ShaderCodeType::eShaderSlang;
		/*
			If it is ShaderCodeType::eShaderSlang, data will take any valid slang shader and
			compile it to the native byte code on the runtime and saves it to a cache
			or something like that. If it is a ShaderCodeType::eNativeByteCode, data must be
			a valid native byte code blob. (spirv for vulkan, dxil for dx12)
		 */
		std::string_view data;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_SHADERDESCRIPTOR_HPP
