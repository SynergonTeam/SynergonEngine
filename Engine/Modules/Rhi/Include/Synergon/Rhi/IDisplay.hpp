#ifndef SYNERGON_RHI_IDISPLAY_HPP
#define SYNERGON_RHI_IDISPLAY_HPP

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/ICommandQueue.hpp"
#include "Synergon/Rhi/ITexture.hpp"

namespace Synergon::Rhi {
	typedef void *WindowHandle;

	class IDisplay {
	   public:
		virtual ~IDisplay() = default;

		virtual void resize(uint32_t width, uint32_t height) = 0;

		virtual bool getCurrentTextureIndex(uint32_t &index) const                                     = 0;
		virtual bool present(uint32_t index, const std::shared_ptr<ICommandQueue> &commandQueue) const = 0;

		virtual std::span<const std::shared_ptr<ITexture>> getDisplayTextures() const = 0;

		virtual uint32_t getWidth() const  = 0;
		virtual uint32_t getHeight() const = 0;

		virtual WindowHandle getWindowHandle() const = 0;

		virtual TextureFormat      getTextureFormat() const = 0;
		virtual TextureUsage::Type getTextureUsage() const  = 0;

		virtual PresentMode        getPresentMode() const        = 0;
		virtual CompositeAlphaMode getCompositeAlphaMode() const = 0;
	};
}  // namespace Synergon::Rhi

#endif  // #ifndef SYNERGON_RHI_IDISPLAY_HPP
