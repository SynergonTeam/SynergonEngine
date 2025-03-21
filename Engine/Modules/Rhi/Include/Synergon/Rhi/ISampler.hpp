#pragma once

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	class ISampler {
	   public:
		virtual ~ISampler() = default;

		virtual AddressMode getAddressModeU() const = 0;
		virtual AddressMode getAddressModeV() const = 0;
		virtual AddressMode getAddressModeW() const = 0;

		virtual Filter getMinFilter() const    = 0;
		virtual Filter getMagFilter() const    = 0;
		virtual Filter getMipMapFilter() const = 0;

		virtual CompareOp getCompareOp() const = 0;

		virtual float    getLodMinClamp() const   = 0;
		virtual float    getLodMaxClamp() const   = 0;
		virtual uint16_t getMaxAnisotropy() const = 0;
	};

}  // namespace Synergon::Rhi
