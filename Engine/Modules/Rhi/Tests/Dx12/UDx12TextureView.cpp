#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12TextureView, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        constexpr TextureDescriptor textureDescriptor{};
        std::shared_ptr<ITexture> texture = device->createTexture(textureDescriptor);

        constexpr TextureViewDescriptor viewDescriptor{};

        ASSERT_NO_THROW(std::shared_ptr<ITextureView> textureView = device->createTextureView(viewDescriptor));
    }
}
