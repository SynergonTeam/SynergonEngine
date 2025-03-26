#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(DeviceTest, DeviceInitialization) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		ASSERT_NE(device, nullptr);
	}
}  // namespace Synergon::Rhi
