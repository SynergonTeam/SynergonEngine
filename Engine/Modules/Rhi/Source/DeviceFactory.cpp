#include "Synergon/Rhi/Factory/DeviceFactory.hpp"

#include "Dx12/Dx12Device.hpp"

namespace Synergon::Rhi {

	std::unique_ptr<IDevice> DeviceFactory::createDevice(const ApiChoice choice,  const DeviceFactoryFunc &customFactoryFunction){
		switch (choice){
			case ApiChoice::eDirectx12: {
				return CreateDx12Device();
			}
			case ApiChoice::eVulkan: {

			}
			case ApiChoice::eCustom: {
				if (customFactoryFunction == nullptr) {
					// todo: assert with assert class from core
					return nullptr;
				}
				return customFactoryFunction();
			}
			default: ;
		}

		return nullptr;
	}
}
