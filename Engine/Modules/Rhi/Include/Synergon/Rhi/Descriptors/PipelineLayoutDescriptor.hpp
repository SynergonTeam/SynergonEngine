#ifndef SYNERGON_RHI_PIPELINELAYOUTDESCRIPTOR_HPP
#define SYNERGON_RHI_PIPELINELAYOUTDESCRIPTOR_HPP

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/IShaderInputLayout.hpp"

#include <memory>

namespace Synergon::Rhi {
	struct PushConstantRange {
		uint32_t          offset;
		uint32_t          size;
		ShaderStage::Type stage;
	};

	struct PipelineLayoutDescriptor {
		std::span<std::shared_ptr<IShaderInputLayout>> shaderInputLayouts;
		std::span<PushConstantRange>                   pushConstantRanges;
	};
}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_PIPELINELAYOUTDESCRIPTOR_HPP
