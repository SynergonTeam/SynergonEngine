#pragma once

#include <wrl.h>
#include <d3d12.h>
#include "SDx12Utils.hpp"


namespace Synergon::Rhi {
	class SDx12Buffer : public IBuffer {
	public:
		SDx12Buffer(const Microsoft::WRL::ComPtr<ID3D12Device>& device, const BufferDescriptor& descriptor);

		void* map(BufferMapType type = BufferMapType::eWrite) override;
		void  unmap() override;

		BufferMapState	  getMapState() const override;
		MemoryUsage       getMemoryUsage() const override;
		BufferUsage::Type getUsage() const override;
		uint64_t          getSize() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> m_Buffer;

	};

}  // namespace Synergon::Rhi
