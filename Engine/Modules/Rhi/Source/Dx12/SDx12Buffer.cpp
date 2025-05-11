#include "SDx12Buffer.hpp"

namespace Synergon::Rhi {
	SDx12Buffer::SDx12Buffer(const Microsoft::WRL::ComPtr<ID3D12Device> &device, const BufferDescriptor &descriptor) {
		D3D12_RESOURCE_DESC bufferDesc = {};
		bufferDesc.Dimension           = D3D12_RESOURCE_DIMENSION_BUFFER;
		bufferDesc.Alignment           = 0;
		bufferDesc.Width               = descriptor.size;
		bufferDesc.Height              = 1;
		bufferDesc.DepthOrArraySize    = 1;
		bufferDesc.MipLevels           = 1;
		bufferDesc.Format              = DXGI_FORMAT_UNKNOWN;
		bufferDesc.SampleDesc.Count    = 1;
		bufferDesc.SampleDesc.Quality  = 0;
		bufferDesc.Layout              = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		bufferDesc.Flags               = D3D12_RESOURCE_FLAG_NONE;

		if (descriptor.usage & BufferUsage::eStorage) {
			bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		}

		D3D12_HEAP_PROPERTIES heapProps = {};
		heapProps.CreationNodeMask      = 1;
		heapProps.VisibleNodeMask       = 1;
		heapProps.CPUPageProperty       = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProps.MemoryPoolPreference  = D3D12_MEMORY_POOL_UNKNOWN;

		switch (descriptor.memoryUsage) {
			case MemoryUsage::eGpu:
				heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;  // GPU-only
				break;
			case MemoryUsage::eCpu:
				heapProps.Type                 = D3D12_HEAP_TYPE_CUSTOM;
				heapProps.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE;
				heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
				break;
			case MemoryUsage::eCpuToGpu:
				heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;  // CPU write, GPU read
				break;
			case MemoryUsage::eGpuToCpu:
				heapProps.Type = D3D12_HEAP_TYPE_READBACK;  // GPU write, CPU read
				break;
		}

		D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

		if (descriptor.usage & BufferUsage::eTransferDst) {
			initialState = D3D12_RESOURCE_STATE_COPY_DEST;
		} else if (descriptor.usage & BufferUsage::eTransferSrc) {
			initialState = D3D12_RESOURCE_STATE_COPY_SOURCE;
		} else if (descriptor.usage & BufferUsage::eIndex) {
			initialState = D3D12_RESOURCE_STATE_INDEX_BUFFER;
		} else if (descriptor.usage & BufferUsage::eVertex) {
			initialState = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
		} else if (descriptor.usage & BufferUsage::eUniform) {
			initialState = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
		} else if (descriptor.usage & BufferUsage::eIndirect) {
			initialState = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
		} else if (descriptor.usage & BufferUsage::eStorage) {
			initialState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		}

		if (descriptor.memoryUsage == MemoryUsage::eCpuToGpu) {
			initialState = D3D12_RESOURCE_STATE_GENERIC_READ;
		} else if (descriptor.memoryUsage == MemoryUsage::eGpuToCpu) {
			initialState = D3D12_RESOURCE_STATE_COPY_DEST;
		}

		SDx12Utils::ThrowIfFailed(device->CreateCommittedResource(
			&heapProps,
			D3D12_HEAP_FLAG_NONE,
			&bufferDesc,
			initialState,
			nullptr,
		    IID_PPV_ARGS(&m_Buffer)));
	}

	void *SDx12Buffer::map(BufferMapType type) {
		return nullptr;
	}

	void SDx12Buffer::unmap() {
	}

	BufferMapState SDx12Buffer::getMapState() const {
		return BufferMapState();
	}

	MemoryUsage SDx12Buffer::getMemoryUsage() const {
		return MemoryUsage();
	}

	BufferUsage::Type SDx12Buffer::getUsage() const {
		return BufferUsage::Type();
	}

	uint64_t SDx12Buffer::getSize() const {
		return 0;
	}

}  // namespace Synergon::Rhi
