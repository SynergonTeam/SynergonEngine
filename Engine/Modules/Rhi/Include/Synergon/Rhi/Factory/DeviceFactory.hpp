#ifndef SYNERGON_RHI_DEVICEFACTORY_HPP
#define SYNERGON_RHI_DEVICEFACTORY_HPP

#include "Synergon/Rhi/IDevice.hpp"

#include <memory>
#include <functional>

namespace Synergon::Rhi {
	enum class ApiChoice {
		eDirectx12,
		eVulkan,
		eCustom,
	};

	using DeviceFactoryFunc = std::function<std::unique_ptr<IDevice>()>;

	class DeviceFactory {
	   public:
		static std::unique_ptr<IDevice> createDevice(ApiChoice choice, const DeviceFactoryFunc &customFactoryFunction = nullptr);

	   private:
		DeviceFactory() = default;
	};

}  // namespace Synergon::Rhi

#endif  // SYNERGON_RHI_DEVICEFACTORY_HPP
