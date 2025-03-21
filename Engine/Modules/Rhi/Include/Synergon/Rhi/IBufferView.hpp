#ifndef SYNERGON_ENGINE_IBUFFERVIEW_HPP
#define SYNERGON_ENGINE_IBUFFERVIEW_HPP

namespace Synergon::Rhi {
	class IBufferView {
	   public:
		virtual ~IBufferView() = default;

		virtual std::shared_ptr<IShaderInputPool> getInputPool() const = 0;
		virtual std::shared_ptr<IBuffer>          getBuffer() const    = 0;

		virtual BufferUsage::Type getUsage() const  = 0;
		virtual uint64_t          getOffset() const = 0;
		virtual uint64_t          getSize() const   = 0;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_ENGINE_IBUFFERVIEW_HPP
