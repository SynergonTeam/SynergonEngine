#ifndef SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP
#define SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"

#include <cstdint>

namespace Synergon::Rhi {
	typedef void* WindowHandle;

	struct DisplayDescriptor {
		WindowHandle windowHandle = nullptr;

		TextureFormat      format;
		TextureUsage::Type usage;

		PresentMode        presentMode        = PresentMode::eFifo;
		CompositeAlphaMode compositeAlphaMode = CompositeAlphaMode::eOpaque;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_DISPLAYDESCRIPTOR_HPP
