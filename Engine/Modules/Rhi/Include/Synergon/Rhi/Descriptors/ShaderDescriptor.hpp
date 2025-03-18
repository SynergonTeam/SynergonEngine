#ifndef SYNERGON_RHI_SHADERDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERDESCRIPTOR_HPP

#include <cstdint>
#include <string>

namespace Synergon::Rhi {

	enum class ShaderCompileType {
		eRuntime,
		eCompileTime,
	};

	struct ShaderDescriptor {
		ShaderCompileType type = ShaderCompileType::eRuntime;
		// if it is runtime ShaderDescriptor this is Slang shader content, if it is a CompileTime ShaderDescriptor this is the path to the shader without the file extension
		std::string_view data;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_SHADERDESCRIPTOR_HPP
