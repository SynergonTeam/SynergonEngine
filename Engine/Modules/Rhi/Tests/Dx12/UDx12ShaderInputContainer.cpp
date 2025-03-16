#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
    TEST(Dx12ShaderInputContainer, DefaultConstruction) {
        const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

        std::vector<ShaderInputLayoutEntry> inputEntry {
                {0, static_cast<ShaderStage::Type>(ShaderStage::eVertex | ShaderStage::eFragment), ShaderInputType::eStorageBuffer}
        };

        ShaderInputLayoutDescriptor inputLayoutDescriptor;
        inputLayoutDescriptor.entries = inputEntry;

        const auto inputLayout = device->createShaderInputLayout(inputLayoutDescriptor);

        ShaderInputContainerDescriptor inputContainerDescriptor;
        inputContainerDescriptor.layout = inputLayout;

        ASSERT_NO_THROW(auto shaderInputContainer = device->createShaderInputContainer(inputContainerDescriptor));
    }
}