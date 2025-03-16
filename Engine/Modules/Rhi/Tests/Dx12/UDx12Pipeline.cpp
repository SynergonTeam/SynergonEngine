#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12Pipeline, EmptyLayoutDefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        std::vector<std::shared_ptr<IShaderInputLayout>> inputLayouts = {};
        std::vector<PushConstantRange> pushConstantRanges = {};

        PipelineLayoutDescriptor pipelineLayoutDescriptor;
        pipelineLayoutDescriptor.shaderInputLayouts = inputLayouts;
        pipelineLayoutDescriptor.pushConstantRanges = pushConstantRanges;

        std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

        RasterizerPipelineDescriptor rasterizerPipelineDescriptor{};
        rasterizerPipelineDescriptor.layout = layout;

        EXPECT_NO_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
    }

    TEST(Dx12Pipeline, ComputeEmptyConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        PipelineLayoutDescriptor pipelineLayoutDescriptor;
        pipelineLayoutDescriptor.shaderInputLayouts = {};
        pipelineLayoutDescriptor.pushConstantRanges = {};

        const std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

        ComputePipelineDescriptor computePipelineDescriptor;
        computePipelineDescriptor.layout = layout;
        computePipelineDescriptor.computeShaderDescriptor = {}; // Empty/dummy shader descriptor
        // computePipelineDescriptor.entryPoint = "main";

        EXPECT_NO_THROW(device->createComputePipeline(computePipelineDescriptor));
    }

    TEST(Dx12Pipeline, RasterizerNullLayout) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        RasterizerPipelineDescriptor rasterizerPipelineDescriptor;
        rasterizerPipelineDescriptor.layout = nullptr; // intentionally null
        rasterizerPipelineDescriptor.inputLayouts = {};
        rasterizerPipelineDescriptor.vertexShaderDescriptor = {};
        rasterizerPipelineDescriptor.fragmentShaderDescriptor = {};
        rasterizerPipelineDescriptor.colorAttachmentFormats = {};
        rasterizerPipelineDescriptor.depthStencil = {};
        rasterizerPipelineDescriptor.rasterizer = {};
        rasterizerPipelineDescriptor.colorBlend = {};
        rasterizerPipelineDescriptor.multisample = {};

        EXPECT_ANY_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
    }

    TEST(Dx12Pipeline, ComputeNullLayout) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        ComputePipelineDescriptor computePipelineDescriptor;
        computePipelineDescriptor.layout = nullptr;
        computePipelineDescriptor.computeShaderDescriptor = {};
        // computePipelineDescriptor.entryPoint = "main";

        EXPECT_ANY_THROW(device->createComputePipeline(computePipelineDescriptor));
    }

    TEST(Dx12Pipeline, RasterizerWithVertexInputAndDepthStencil) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        // Create pipeline layout.
        PipelineLayoutDescriptor pipelineLayoutDescriptor;
        pipelineLayoutDescriptor.shaderInputLayouts = {};
        pipelineLayoutDescriptor.pushConstantRanges = {};
        std::shared_ptr<IPipelineLayout> layout = device->createPipelineLayout(pipelineLayoutDescriptor);

        std::vector<VertexAttribute> vertexAttributes = {
            { VertexFormat::eUint8, 0, 0 }
        };

        std::vector<VertexInputLayout> inputLayouts = {
            {VertexStepMode::eVertex, sizeof(uint8_t), std::span(vertexAttributes) }
        };

        DepthStencilState depthStencilState{};
        depthStencilState.format = TextureFormat::eDepth32Float;
        depthStencilState.depthTestEnable = true;
        depthStencilState.depthWriteEnable = true;
        depthStencilState.minDepthBounds = 0.0f;
        depthStencilState.maxDepthBounds = 1.0f;
        depthStencilState.depthCompareOp = CompareOp::eLess;
        depthStencilState.stencilTestEnable = false;
        depthStencilState.stencilReadMask = 0xff;
        depthStencilState.stencilWriteMask = 0xff;
        // Initialize stencil face states.
        depthStencilState.front = { CompareOp::eAlways, StencilOp::eKeep, StencilOp::eKeep, StencilOp::eKeep };
        depthStencilState.back  = { CompareOp::eAlways, StencilOp::eKeep, StencilOp::eKeep, StencilOp::eKeep };

        RasterizerPipelineDescriptor rasterizerPipelineDescriptor;
        rasterizerPipelineDescriptor.layout = layout;
        rasterizerPipelineDescriptor.inputLayouts = std::span<VertexInputLayout>(inputLayouts);
        rasterizerPipelineDescriptor.vertexShaderDescriptor = {};   // todo: create dummy shader descriptor
        rasterizerPipelineDescriptor.fragmentShaderDescriptor = {}; // todo: create dummy shader descriptor
        std::vector colorFormats = { TextureFormat::eRGBA8Unorm };
        rasterizerPipelineDescriptor.colorAttachmentFormats = std::span<TextureFormat>(colorFormats);
        rasterizerPipelineDescriptor.depthStencil = depthStencilState;
        rasterizerPipelineDescriptor.rasterizer.topology = PrimitiveTopology::eTriangleList;
        rasterizerPipelineDescriptor.rasterizer.cullMode = CullMode::eBack;
        rasterizerPipelineDescriptor.rasterizer.frontFace = FrontFace::eClockWise;
        rasterizerPipelineDescriptor.rasterizer.polygonMode = PolygoneMode::eFill;
        // Use default color blend and multisample states.
        rasterizerPipelineDescriptor.colorBlend = {};
        rasterizerPipelineDescriptor.multisample = {};

        EXPECT_NO_THROW(device->createRasterizerPipeline(rasterizerPipelineDescriptor));
    }
}