#pragma once

#include "Synergon\Events\Callbacks.hpp"

namespace Synergon::Events {
	class EventObserver : public ACallbackMannager {
	   public:
		EventObserver()           = default;
		~EventObserver() override = default;

		template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		void process(const Event& event) {
			const size_t eventHashCode = typeid(Event).hash_code();

			const auto& callbacks = m_IEventTypeCallbackMap[eventHashCode];

			for (const auto& [_, callback] : callbacks) {
				callback(&event);
			}
		}
	};
}  // namespace Synergon::Events
