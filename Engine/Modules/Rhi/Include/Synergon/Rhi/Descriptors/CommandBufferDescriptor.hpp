#ifndef SYNERGON_RHI_COMMANDBUFFERDESCRIPTOR_HPP
#define SYNERGON_RHI_COMMANDBUFFERDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	struct CommandBufferDescriptor {
		bool oneTimeSubmit = true;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_COMMANDBUFFERDESCRIPTOR_HPP
