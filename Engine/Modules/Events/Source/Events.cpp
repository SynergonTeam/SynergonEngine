#include "Synergon/Events.hpp"

namespace Synergon::Events {
	EventDispatcher::EventDispatcher(EventDispatcher &&other) {
		if (&other != this) {
			this->m_IEventTypeCallbackMap = std::move(other.m_IEventTypeCallbackMap);
			this->m_IEventIndicesMap      = std::move(other.m_IEventIndicesMap);
			this->m_IEventVectorMap       = std::move(other.m_IEventVectorMap);

			other.m_IEventTypeCallbackMap.clear();
			other.m_IEventIndicesMap.clear();
			other.m_IEventVectorMap.clear();
		}
	}

	EventDispatcher &EventDispatcher::operator=(EventDispatcher &&other) {
		if (&other != this) {
			this->m_IEventTypeCallbackMap = std::move(other.m_IEventTypeCallbackMap);
			this->m_IEventIndicesMap      = std::move(other.m_IEventIndicesMap);
			this->m_IEventVectorMap       = std::move(other.m_IEventVectorMap);

			other.m_IEventTypeCallbackMap.clear();
			other.m_IEventIndicesMap.clear();
			other.m_IEventVectorMap.clear();
		}

		return *this;
	}
}  // namespace Synergon::Events
