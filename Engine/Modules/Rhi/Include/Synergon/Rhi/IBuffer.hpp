#pragma once

#include "Synergon/Rhi/Enums.hpp"

#include <memory>

namespace Synergon::Rhi {

	class IBuffer {
	   public:
		virtual ~IBuffer() = default;

		virtual void* map(BufferMapType type = BufferMapType::eWrite) = 0;
		virtual void  unmap()                                         = 0;

		virtual BufferMapState getMapState() const = 0;

		virtual MemoryUsage       getMemoryUsage() const = 0;
		virtual BufferUsage::Type getUsage() const       = 0;
		virtual uint64_t          getSize() const        = 0;
	};
}  // namespace Synergon::Rhi
