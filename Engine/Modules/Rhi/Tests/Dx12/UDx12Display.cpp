#include "Synergon/Rhi/IDisplay.hpp"
#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
	TEST(Dx12Display, ConstructionWindows) {
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

		DisplayDescriptor displayDescriptor;
		displayDescriptor.height = 5;
		displayDescriptor.width = 5;
		displayDescriptor.windowHandle = nullptr;

		EXPECT_NO_THROW(device->createDisplay(displayDescriptor));
	}

	TEST(Dx12Display, ConstructionZeroDimension) {
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

		DisplayDescriptor displayDescriptor;
		displayDescriptor.height = 0;
		displayDescriptor.width = 0;
		displayDescriptor.windowHandle = nullptr;

		EXPECT_THROW(device->createDisplay(displayDescriptor), std::exception);
	}
}