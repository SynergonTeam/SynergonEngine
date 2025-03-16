#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include <gtest/gtest.h>

namespace Synergon::Rhi {
	TEST(Dx12Device, DeviceCreation) {
		ASSERT_NO_THROW(std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12));
	}

	TEST(Dx12Device, DeviceCreationNotNull) {
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(ApiChoice::eDirectx12);

		ASSERT_TRUE(device != nullptr);
	}

	ApiChoice stringToApiChoice(const std::string& apiChoice) {

		if (apiChoice == "Directx12") {
			return ApiChoice::eDirectx12;
		}
		if (apiChoice == "Vulkan") {
			return ApiChoice::eVulkan;
		}

		return ApiChoice::eCustom;
	}

	// todo:
	class DeviceTest : public ::testing::TestWithParam<std::string> {};

	TEST_P(DeviceTest, DeviceInitialization) {
		std::string apiName = GetParam();
		const std::unique_ptr<IDevice> device = DeviceFactory::createDevice(stringToApiChoice(apiName));


		ASSERT_NE(device, nullptr);
	}

	INSTANTIATE_TEST_SUITE_P(
	ApiChoice, DeviceTest,
	::testing::Values("Vulkan", "Directx12"));
}
