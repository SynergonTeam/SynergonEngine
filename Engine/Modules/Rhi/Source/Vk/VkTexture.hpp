#ifndef SYNERGON_RHI_VKTEXTURE_HPP
#define SYNERGON_RHI_VKTEXTURE_HPP

#include "Synergon/Rhi/Descriptors/TextureViewDescriptor.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

namespace Synergon::Rhi {
	class VkTexture {
	   public:
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor);
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_VKTEXTURE_HPP