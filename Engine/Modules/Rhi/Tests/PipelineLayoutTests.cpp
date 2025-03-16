#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(PipelineLayoutTest, DefaultConstruction) {
		const std::string apiName = GetParam();
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr PipelineLayoutDescriptor pipelineLayoutDescriptor{};

		EXPECT_NO_THROW(device->createPipelineLayout(pipelineLayoutDescriptor));
	}

	INSTANTIATE_TEST_SUITE_P(
	ApiChoice, PipelineLayoutTest,
	::testing::Values("Vulkan", "Directx12"));
}
