#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>


namespace Synergon::Rhi {
	TEST(Dx12PipelineLayout, EmptyConstruction) {
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

		std::vector<std::shared_ptr<IShaderInputLayout>> inputLayouts =
		{
		};

		std::vector<PushConstantRange> pushConstantRanges =
		{
		};

		PipelineLayoutDescriptor pipelineLayoutDescriptor;
		pipelineLayoutDescriptor.shaderInputLayouts = inputLayouts;
		pipelineLayoutDescriptor.pushConstantRanges = pushConstantRanges;

		EXPECT_NO_THROW(device->createPipelineLayout(pipelineLayoutDescriptor));
	}
}
