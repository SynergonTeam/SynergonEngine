#ifndef SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP
#define SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP

#include <cstdint>

#include <Synergon/Rhi/Enums.hpp>

namespace Synergon::Rhi {
	struct DisplayDescriptor {
		void* windowHandle = nullptr;

		uint32_t width{};
		uint32_t height{};

		PresentMode        presentMode;
		CompositeAlphaMode compositeAlphaMode;
	};
}

#endif //SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP
