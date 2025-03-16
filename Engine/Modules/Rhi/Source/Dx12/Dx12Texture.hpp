#ifndef SYNERGON_RHI_DX12TEXTURE_HPP
#define SYNERGON_RHI_DX12TEXTURE_HPP

#include "Synergon/Rhi/Descriptors/TextureViewDescriptor.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>

namespace Synergon::Rhi {
	class Dx12Texture {
	   public:
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor);
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_DX12TEXTURE_HPP