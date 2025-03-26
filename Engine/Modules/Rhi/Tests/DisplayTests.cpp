#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(DisplayTest, ConstructionWindows) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		DisplayDescriptor displayDescriptor;
		// displayDescriptor.height       = 5;
		// displayDescriptor.width        = 5;
		displayDescriptor.windowHandle = nullptr;

		EXPECT_NO_THROW(device->createDisplay(displayDescriptor));
	}

	TEST_P(DisplayTest, ConstructionZeroDimension) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		DisplayDescriptor displayDescriptor;
		// displayDescriptor.height       = 0;
		// displayDescriptor.width        = 0;
		displayDescriptor.windowHandle = nullptr;

		EXPECT_THROW(device->createDisplay(displayDescriptor), std::exception);
	}
}  // namespace Synergon::Rhi