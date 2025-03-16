#ifndef SYNERGON_RHI_SHADERDESCRIPTOR_HPP
#define SYNERGON_RHI_SHADERDESCRIPTOR_HPP

#include <cstdint>
#include <string>

namespace Synergon::Rhi {
	struct ShaderDescriptor {
		std::string_view data;
		uint64_t         size;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_ISHADER_HPP
