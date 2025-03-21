#ifndef SYNERGON_RHI_ISHADERINPUTPOOL_HPP
#define SYNERGON_RHI_ISHADERINPUTPOOL_HPP

#include "Synergon/Rhi/Enums.hpp"

namespace Synergon::Rhi {
	class IShaderInputPool {
	   public:
		virtual ~IShaderInputPool() = default;

		virtual ShaderInputType getType() const  = 0;
		virtual uint32_t        getCount() const = 0;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_ISHADERINPUTPOOL_HPP
