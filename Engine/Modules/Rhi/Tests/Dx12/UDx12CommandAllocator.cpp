#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>


namespace Synergon::Rhi {
    TEST(Dx12CommandAllocator, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr CommandAllocatorDescriptor descriptor{};

        EXPECT_NO_THROW(std::unique_ptr<ICommandAllocator> sampler = device->createCommandAllocator(descriptor));
    }
}