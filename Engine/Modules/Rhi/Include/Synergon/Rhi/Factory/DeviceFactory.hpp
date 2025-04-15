#pragma once

#include "Synergon/Rhi/IDevice.hpp"
#include "Synergon/Rhi/Enums.hpp"

#include <memory>
#include <functional>

namespace Synergon::Rhi {
	using DeviceFactoryFunc = std::function<std::unique_ptr<IDevice>()>;

	class DeviceFactory {
	   public:
		static std::unique_ptr<IDevice> createDevice(ApiChoice choice, const DeviceFactoryFunc &customFactoryFunction = nullptr);

	   private:
		DeviceFactory() = default;
	};

}  // namespace Synergon::Rhi
