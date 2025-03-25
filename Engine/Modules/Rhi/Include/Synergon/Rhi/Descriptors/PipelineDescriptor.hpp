#pragma once

#include "Synergon/Rhi/Enums.hpp"
#include "Synergon/Rhi/IShader.hpp"
#include "Synergon/Rhi/IPipelineLayout.hpp"

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
		uint32_t     offset;
		uint32_t     location;
	};

	struct VertexInputLayout {
		VertexStepMode stepMode = VertexStepMode::eVertex;

		uint64_t                   arrayStride;
		std::span<VertexAttribute> attributes;
	};

	struct RasterizerState {
		PrimitiveTopology topology    = PrimitiveTopology::eTriangleList;
		PolygoneMode      polygonMode = PolygoneMode::eFill;
		CullMode          cullMode    = CullMode::eNone;
		FrontFace         frontFace   = FrontFace::eCounterClockWise;
	};

	struct ColorBlendState {
		bool blendEnable = false;

		BlendComponent color;
		BlendComponent alpha;
	};

	struct DepthStencilState {
		TextureFormat format;

		bool  depthTestEnable  = true;
		bool  depthWriteEnable = true;
		float minDepthBounds   = 0.0f;
		float maxDepthBounds   = 1.0f;

		CompareOp depthCompareOp = CompareOp::eLess;

		bool     stencilTestEnable = false;
		uint32_t stencilReadMask   = 0xFF;
		uint32_t stencilWriteMask  = 0xFF;

		StencilFaceState front;
		StencilFaceState back;
	};

	struct MultisampleState {
		SampleCount sampleCount     = SampleCount::e1;
		bool        alphaToCoverage = false;
	};

	struct ShaderModule {
		std::shared_ptr<IShader> shader;
		std::string              entryPoint;
	};

	struct RasterizerPipelineDescriptor {
		std::shared_ptr<IPipelineLayout> layout;
		std::span<VertexInputLayout>     inputLayouts;

		ShaderModule vertexShaderModule;
		ShaderModule fragmentShaderModule;

		RasterizerState  rasterizer;
		ColorBlendState  colorBlend;
		MultisampleState multisample;

		std::span<TextureFormat>         colorAttachmentFormats;
		std::optional<DepthStencilState> depthStencil;
	};

	struct ComputePipelineDescriptor {
		std::shared_ptr<IPipelineLayout> layout;
		ShaderModule                     shaderModule;
	};
}  // namespace Synergon::Rhi
