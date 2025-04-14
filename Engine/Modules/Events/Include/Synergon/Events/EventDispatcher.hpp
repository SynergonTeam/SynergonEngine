#pragma once

#include "Synergon/Events/Callbacks.hpp"

#include <memory>

namespace Synergon::Events {
	class EventDispatcher : public ACallbackMannager {
	   public:
		EventDispatcher()           = default;
		~EventDispatcher() override = default;

		EventDispatcher(const EventDispatcher&)            = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;

		EventDispatcher(EventDispatcher&& other);
		EventDispatcher& operator=(EventDispatcher&& other);

		template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		void addEvent(const Event& event) {
			const IEventType eventType = typeid(Event);

			if (m_IEventVectorMap.find(eventType) == m_IEventVectorMap.end()) {
				m_IEventVectorMap[eventType] = std::make_unique<EventVector<Event>>();
			}

			EventVector<Event>* pEventVector = dynamic_cast<EventVector<Event>*>(m_IEventVectorMap[eventType].get());

			m_IEventIndicesMap[eventType].push_back(pEventVector->size());
			pEventVector->add(event);
		}

		void dispatch() {
			for (const auto& [eventType, eventIndices] : m_IEventIndicesMap) {
				const auto& callbacks    = m_IEventTypeCallbackMap[eventType];
				const auto& iEventVector = m_IEventVectorMap[eventType];

				for (const auto& [_, callback] : callbacks)
					for (const uint32_t& eventIndex : eventIndices)
						callback(iEventVector->get(eventIndex));
			}

			m_IEventIndicesMap.clear();
			m_IEventVectorMap.clear();
		}

	   private:
		class IEventVector {
		   public:
			virtual ~IEventVector() = default;

			virtual uint32_t      size() const              = 0;
			virtual const IEvent* get(uint32_t index) const = 0;
		};

		template <typename Event, typename = std::enable_if_t<std::is_base_of<IEvent, Event>::value>>
		class EventVector : public IEventVector {
		   public:
			void add(const Event& event) {
				m_Events.push_back(event);
			}

			uint32_t size() const override {
				return static_cast<uint32_t>(m_Events.size());
			}

			const IEvent* get(std::uint32_t index) const override {
				return &m_Events[index];
			}

		   private:
			std::vector<Event> m_Events;
		};

	   private:
		std::map<IEventType, std::unique_ptr<IEventVector>> m_IEventVectorMap;
		std::map<IEventType, std::vector<std::uint32_t>>    m_IEventIndicesMap;
	};
}  // namespace Synergon::Events
