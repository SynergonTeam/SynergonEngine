#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12Texture, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr TextureDescriptor descriptor{};

        ASSERT_NO_THROW(std::shared_ptr<ITexture> texture = device->createTexture(descriptor));
    }
}