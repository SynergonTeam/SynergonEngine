#ifndef SYNERGON_RHI_PIPELINEDESCRIPTOR_HPP
#define SYNERGON_RHI_PIPELINEDESCRIPTOR_HPP

#include "Synergon/Rhi/Descriptors/ShaderDescriptor.hpp"
#include "Synergon/Rhi/IPipelineLayout.hpp"
#include "Synergon/Rhi/Enums.hpp"

#include <memory>
#include <optional>
#include <span>
#include <string>

namespace Synergon::Rhi {

	struct StencilFaceState {
		CompareOp compareOp;
		StencilOp failOp;
		StencilOp passOp;
		StencilOp depthFailOp;
	};

	struct BlendComponent {
		BlendFactor srcFactor;
		BlendFactor dstFactor;
		BlendOp     op;
	};

	struct VertexAttribute {
		VertexFormat format;
		uint64_t     offset;
		uint32_t     location;
	};

	struct VertexInputLayout {
		VertexStepMode				stepMode{};
		uint64_t					arrayStride{};
		std::span<VertexAttribute>	attributes;
	};

	struct RasterizerState {
		PrimitiveTopology 	topology =	PrimitiveTopology::eTriangleList;
		PolygoneMode polygonMode =		PolygoneMode::eFill;
		CullMode cullMode =				CullMode::eNone;
		FrontFace frontFace =			FrontFace::eClockWise;
	};

	struct ColorBlendState {
		BlendComponent color;
		BlendComponent alpha;
	};

	struct DepthStencilState {
		TextureFormat format;

		bool  depthTestEnable;
		bool  depthWriteEnable;
		float minDepthBounds;
		float maxDepthBounds;

		CompareOp depthCompareOp;

		bool     stencilTestEnable;
		uint32_t stencilReadMask;
		uint32_t stencilWriteMask;

		StencilFaceState front;
		StencilFaceState back;
	};

	struct MultisampleState {
		SampleCount sampleCount;
		bool        alphaToCoverage;
	};

	struct RasterizerPipelineDescriptor {
		std::shared_ptr<IPipelineLayout> layout;
		std::span<VertexInputLayout> inputLayouts;

		ShaderDescriptor fragmentShaderDescriptor;
		ShaderDescriptor vertexShaderDescriptor;

		std::span<TextureFormat> colorAttachmentFormats;
		std::optional<DepthStencilState> depthStencil;

		RasterizerState  rasterizer;
		ColorBlendState  colorBlend;
		MultisampleState multisample;
	};

	struct ComputePipelineDescriptor {
		std::shared_ptr<IPipelineLayout> layout;
		ShaderDescriptor computeShaderDescriptor;
	};

}

#endif //#ifndef SYNERGON_RHI_PIPELINEDESCRIPTOR_HPP
