#pragma once

#include "Synergon\Events\IEvent.hpp"

#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <functional>
#include <map>
#include <cstdint>

namespace Synergon::Events {
	using EventCallbackHandle = uint32_t;

	template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
	using EventCallback = void (*)(const Event &event);

	class ACallbackMannager {
	   public:
		ACallbackMannager()          = default;
		virtual ~ACallbackMannager() = default;

		template <typename Event, typename Callback, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		EventCallbackHandle addCallback(Callback &&callback) {
			const IEventType   eventType = typeid(Event).hash_code();
			IEventCallbackMap &callbacks = m_IEventTypeCallbackMap[eventType];

			const EventCallbackHandle handle = callbacks.size();

			callbacks[handle] = [callback = callback](const IEvent *event) {
				callback(*static_cast<const Event *>(event));
			};
			return handle;
		}

		template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		EventCallbackHandle addCallback(EventCallback<Event> callback) {
			const IEventType   eventType = typeid(Event).hash_code();
			IEventCallbackMap &callbacks = m_IEventTypeCallbackMap[eventType];

			const EventCallbackHandle handle = callbacks.size();

			callbacks[handle] = [callback = callback](const IEvent *event) {
				callback(*static_cast<const Event *>(event));
			};
			return handle;
		}

		template <typename Event, typename T, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		EventCallbackHandle addCallback(T *self, void (T::*callback)(const Event &event)) {
			const IEventType   eventType = typeid(Event).hash_code();
			IEventCallbackMap &callbacks = m_IEventTypeCallbackMap[eventType];

			const EventCallbackHandle handle = callbacks.size();

			callbacks[handle] = [callback = callback, self = self](const IEvent *event) {
				(self->*callback)(*static_cast<const Event *>(event));
			};
			return handle;
		}

		template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		void removeCallback(EventCallbackHandle handle) {
			const IEventType   eventType = typeid(Event).hash_code();
			IEventCallbackMap &callbacks = m_IEventTypeCallbackMap[eventType];
			callbacks.erase(handle);
		}

	   protected:
		using IEventType        = uint32_t;
		using IEventCallback    = std::function<void(const IEvent *)>;
		using IEventCallbackMap = std::map<EventCallbackHandle, IEventCallback>;

	   protected:
		std::map<IEventType, IEventCallbackMap> m_IEventTypeCallbackMap;
	};
}  // namespace Synergon::Events
