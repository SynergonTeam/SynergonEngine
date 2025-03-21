#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include <string>

namespace Synergon::Rhi {
	/*
        If it is ShaderCodeType::eShaderSlang, data will take any valid slang shader and
        compile it to the native byte code on the runtime and saves it to a cache
        or something like that. If it is a ShaderCodeType::eNativeByteCode, data must be
        a valid native byte code blob. (spirv for vulkan, dxil for dx12)
     */
	struct ShaderDescriptor {
		ShaderCodeType   type = ShaderCodeType::eShaderSlang;
		std::string_view data;
	};
}  // namespace Synergon::Rhi
