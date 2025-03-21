#pragma	once

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	typedef void* WindowHandle;

	struct DisplayDescriptor {
		WindowHandle windowHandle = nullptr;

		TextureFormat      format;
		TextureUsage::Type usage;

		uint32_t textureCount = 2u;

		PresentMode        presentMode        = PresentMode::eFifo;
		CompositeAlphaMode compositeAlphaMode = CompositeAlphaMode::eOpaque;
	};
}  // namespace Synergon::Rhi
