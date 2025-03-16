#ifndef SYNERGON_RHI_DX12TEXTURE_HPP
#define SYNERGON_RHI_DX12TEXTURE_HPP

#include "Synergon/Rhi/ITexture.hpp"

namespace Synergon::Rhi {
	class Dx12Texture {
	public:
		std::shared_ptr<ITextureView> createTextureView(const TextureViewDescriptor& descriptor);

	private:
	};
}

#endif //#ifndef SYNERGON_RHI_DX12TEXTURE_HPP