#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>


namespace Synergon::Rhi {
    TEST(Dx12Sampler, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr SamplerDescriptor descriptor{};

        EXPECT_NO_THROW(std::shared_ptr<ISampler> sampler = device->createSampler(descriptor));
    }
}
