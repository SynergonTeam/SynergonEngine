#include <Synergon/Samples.hpp>
#include <Synergon/Events.hpp>

#include <iostream>
#include <format>

namespace Synergon {
	using namespace Events;

	class WindowResizeEvent : public IEvent {
	   public:
		WindowResizeEvent(uint32_t width, uint32_t height)
		    : width{width}, height{height} {}

		~WindowResizeEvent() override = default;

		uint32_t width{0u};
		uint32_t height{0u};
	};

	class AppExit : public IEvent {
	   public:
		AppExit() = default;

		AppExit(int32_t exitCode) : exitCode{exitCode} {}

		~AppExit() override = default;

		int32_t exitCode{0};
	};

	class App {
	   public:
		App(EventObserver& observer) : m_pObserver{&observer} {
			m_EventDispatcher.addCallback<WindowResizeEvent>(this, &App::windowResizeCallackForDispatcher);
			m_EventDispatcher.addCallback<AppExit>(this, &App::appExitCallbackForDispatcher);

			m_WindowResizeCallbackHandle =
			    m_pObserver->addCallback<WindowResizeEvent>(this, &App::windowResizeCallackForDispatcher);
			m_AppExitCallbackHandle =
			    m_pObserver->addCallback<AppExit>(this, &App::appExitCallbackForDispatcher);
		}

		~App() {
			//! must clean itself before releasing

			m_pObserver->removeCallback<WindowResizeEvent>(m_WindowResizeCallbackHandle);
			m_pObserver->removeCallback<AppExit>(m_AppExitCallbackHandle);
		}

		void run() {
			uint32_t counter{0u};

			do {
				std::printf("\n");
				if (counter % 3 == 0) {
					WindowResizeEvent newEvent{counter, counter};
					m_pObserver->process(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
					m_EventDispatcher.addEvent<WindowResizeEvent>(newEvent);
				}

				if (counter == 100) {
					m_pObserver->process(AppExit(0u));
					m_EventDispatcher.addEvent<AppExit>(AppExit(0u));
					m_EventDispatcher.addEvent<AppExit>(AppExit(1u));
					m_EventDispatcher.addEvent<AppExit>(AppExit(2u));
					m_EventDispatcher.addEvent<AppExit>(AppExit(3u));
				}

				m_EventDispatcher.dispatch();
			} while (counter != 100);
		}

		void windowResizeCallackForDispatcher(const WindowResizeEvent& event) {
			std::printf("App::m_EventDispatcher: Window Resize {%u, %u}\n", event.width, event.height);
		}

		void windowResizeCallbackForObserver(const WindowResizeEvent& event) {
			std::printf("App::m_EventObserver: Window Resize {%u, %u}\n", event.width, event.height);
		}

		void appExitCallbackForDispatcher(const AppExit& event) {
			std::printf("App::m_EventDispatcher: App Exit with %d code\n", event.exitCode);
		}

		void appExitCallbackForObserver(const AppExit& event) {
			std::printf("App::m_EventObserver: App Exit with %d code\n", event.exitCode);
		}

	   private:
		EventObserver* m_pObserver{nullptr};

		EventDispatcher m_EventDispatcher{};

		EventCallbackHandle m_WindowResizeCallbackHandle{};
		EventCallbackHandle m_AppExitCallbackHandle{};
	};

	void SamplesTempFunction() {
		std::cout << std::vformat("Hello from Synergon::SamplesTempFunction() in {}\n", std::make_format_args(__FILE__));

		EventObserver observer{};

		App app{observer};

		app.run();

		std::printf("Goodbye, World!\n");
	}
}  // namespace Synergon