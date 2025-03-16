#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12ShaderInputLayout, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        std::vector<ShaderInputLayoutEntry> inputEntry {
            {0, static_cast<ShaderStage::Type>(ShaderStage::eVertex | ShaderStage::eFragment), ShaderInputType::eStorageBuffer}
        };

        ShaderInputLayoutDescriptor inputLayoutDescriptor;
        inputLayoutDescriptor.entries = inputEntry;

        ASSERT_NO_THROW(auto inputLayout = device->createShaderInputLayout(inputLayoutDescriptor));
    }

    TEST(Dx12ShaderInputLayout, EmptyConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        std::vector<ShaderInputLayoutEntry> inputEntry {
        };

        ShaderInputLayoutDescriptor inputLayoutDescriptor;
        inputLayoutDescriptor.entries = inputEntry;

        EXPECT_ANY_THROW(auto inputLayout = device->createShaderInputLayout(inputLayoutDescriptor));
    }
}