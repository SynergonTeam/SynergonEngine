#pragma once

#include "Synergon/Rhi/IShaderInputLayout.hpp"
#include "Synergon/Rhi/IShaderInputPool.hpp"

#include <memory>

namespace Synergon::Rhi {
	struct ShaderInputContainerDescriptor {
		std::shared_ptr<IShaderInputLayout> layout;
		std::shared_ptr<IShaderInputPool>   pool;
	};
}  // namespace Synergon::Rhi
