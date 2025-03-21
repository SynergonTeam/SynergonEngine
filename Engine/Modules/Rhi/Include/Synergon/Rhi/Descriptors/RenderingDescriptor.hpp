#ifndef SYNERGON_RHI_RENDERINGDESCRIPTOR_HPP
#define SYNERGON_RHI_RENDERINGDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/ITextureView.hpp"

#include <memory>
#include <span>
#include <optional>

namespace Synergon::Rhi {
	struct ColorAttachment {
		std::shared_ptr<ITextureView> target;

		LoadOp  loadOp  = LoadOp::eLoad;
		StoreOp storeOp = StoreOp::eStore;
		float   clearValue[4];
	};

	struct DepthStencilAttachment {
		std::shared_ptr<ITextureView> target;

		LoadOp  loadOp  = LoadOp::eClear;
		StoreOp storeOp = StoreOp::eStore;
		float   clearValue;
	};

	struct RenderingDescriptor {
		std::span<ColorAttachment> colorAttachments;

		std::optional<DepthStencilAttachment> depthStencilAttachment = std::nullopt;
	};

}  //  namespace Synergon::Rhi

#endif  // SYNERGON_RHI_RENDERINGDESCRIPTOR_HPP
