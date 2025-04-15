#include "TestApiClasses.hpp"

#include "Utils.hpp"

#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

namespace Synergon::Rhi {
	TEST_P(FenceTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr FenceDescriptor descriptor{};

		ASSERT_NO_THROW(auto fence = device->createFence(descriptor));
	}
}  // namespace Synergon::Rhi
