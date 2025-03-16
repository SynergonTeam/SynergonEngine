#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12Fence, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr FenceDescriptor descriptor{};

        ASSERT_NO_THROW(auto fence = device->createFence(descriptor));
    }
}
