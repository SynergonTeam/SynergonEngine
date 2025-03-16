#ifndef SYNERGON_RHI_ISHADER_HPP
#define SYNERGON_RHI_ISHADER_HPP

#include <cstdint>
#include <string>

namespace Synergon::Rhi {
	struct ShaderDescriptor {
		std::string	entryPoint;
		const void* data;
		uint32_t size;
	};
}

#endif //#ifndef SYNERGON_RHI_ISHADER_HPP
