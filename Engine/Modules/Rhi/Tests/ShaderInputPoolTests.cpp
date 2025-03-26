#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(ShaderInputPoolTest, DeviceInitialization) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		ShaderInputPoolDescriptor shaderInputPoolDesc{};
		shaderInputPoolDesc.type  = ShaderInputType::eResource;
		shaderInputPoolDesc.count = 2;

		ASSERT_NO_THROW(auto pool = device->createShaderInputPool(shaderInputPoolDesc));
	}
}  // namespace Synergon::Rhi
