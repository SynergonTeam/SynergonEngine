#ifndef SYNERGON_ENGINE_SHADERINPUTALLOCATORDESCRIPTOR_HPP
#define SYNERGON_ENGINE_SHADERINPUTALLOCATORDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

#include <cstdint>

namespace Synergon::Rhi {
	struct ShaderInputPoolDescriptor {
		ShaderInputType type;
		uint32_t        count;
	};
}  //  namespace Synergon::Rhi

#endif  // SYNERGON_ENGINE_SHADERINPUTALLOCATORDESCRIPTOR_HPP