#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12CommandBuffer, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr CommandAllocatorDescriptor descriptor{};

        const std::unique_ptr<ICommandAllocator> allocator = device->createCommandAllocator(descriptor);

        constexpr CommandBufferDescriptor commandBufferDescriptor{};

        ASSERT_NO_THROW(std::unique_ptr<ICommandBuffer> commandBuffer = allocator->allocateCommandBuffer(commandBufferDescriptor));
    }
}
