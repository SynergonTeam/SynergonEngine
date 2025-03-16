#ifndef SYNERGON_RHI_SHADERINPUTCONTAINERDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERINPUTCONTAINERDESCRIPTOR_HPP

#include <memory>

namespace Synergon::Rhi {
	struct ShaderInputContainerDescriptor {
		std::shared_ptr<IShaderInputLayout> layout;
	};
}

#endif //SYNERGON_RHI_SHADERINPUTCONTAINERDESCRIPTOR_HPP
