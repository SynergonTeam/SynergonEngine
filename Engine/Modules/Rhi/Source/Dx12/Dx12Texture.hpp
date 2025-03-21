#pragma once

#include "Synergon/Rhi/Descriptors/TextureViewDescriptor.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

namespace Synergon::Rhi {
	class Dx12Texture {
	   public:
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor);
	};
}  // namespace Synergon::Rhi
