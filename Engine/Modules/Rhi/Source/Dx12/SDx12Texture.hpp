#pragma once

#include <wrl.h>
#include <d3d12.h>
#include "Synergon/Rhi/Descriptors/TextureDescriptor.hpp"

#include <memory>

namespace Synergon::Rhi {

	/**
	 * @brief DirectX 12 texture class
	 *
	 * This class encapsulates a DirectX 12 texture resource and provides methods for
	 * creating and managing textures in the DirectX 12 API.
	 */
	class SDx12Texture {

	public:
		SDx12Texture(const TextureDescriptor& descriptor) { }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
	};


}  // namespace Synergon::Rhi
