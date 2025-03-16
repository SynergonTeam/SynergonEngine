#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12Buffer, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr BufferDescriptor bufferDescriptor{};

        ASSERT_NO_THROW(std::shared_ptr<IBuffer> buffer = device->createBuffer(bufferDescriptor));
    }
}
