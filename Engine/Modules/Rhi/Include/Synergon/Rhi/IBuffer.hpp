#ifndef SYNERGON_RHI_IBUFFER_HPP
#define SYNERGON_RHI_IBUFFER_HPP

#include <memory>

namespace Synergon::Rhi {

	class IBuffer {
	   public:
		virtual ~IBuffer() = default;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_IBUFFER_HPP