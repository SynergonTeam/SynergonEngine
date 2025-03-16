#include "TestClasses.hpp"

namespace Synergon::Rhi {
    TEST_P(SamplerTest, DefaultConstruction) {
        const std::string apiName = GetParam();
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(StringToApiChoice(apiName));

        constexpr SamplerDescriptor descriptor{};

        EXPECT_NO_THROW(std::shared_ptr<ISampler> sampler = device->createSampler(descriptor));
    }

    INSTANTIATE_TEST_SUITE_P(
    ApiChoice, SamplerTest,
    ::testing::Values("Vulkan", "Directx12"));
}
