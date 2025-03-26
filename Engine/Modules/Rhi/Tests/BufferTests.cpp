#include "TestClasses.hpp"

namespace Synergon::Rhi {
	TEST_P(BufferTest, DefaultConstruction) {
		const std::string              apiName = GetParam();
		const std::unique_ptr<IDevice> device  = DeviceFactory::createDevice(StringToApiChoice(apiName));

		constexpr BufferDescriptor bufferDescriptor{};

		ASSERT_NO_THROW(std::shared_ptr<IBuffer> buffer = device->createBuffer(bufferDescriptor));
	}
}  // namespace Synergon::Rhi
