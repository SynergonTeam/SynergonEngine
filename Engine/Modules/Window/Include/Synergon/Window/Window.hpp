#pragma once

typedef void* NativeWindowHandle;

#include "Synergon/Window/Descriptors/WindowDescriptor.hpp"

class GLFWwindow;

namespace Synergon::Window {

	class Window {
	   public:
		Window(const WindowDescriptor& descriptor);
		~Window();

		Window(const Window&)            = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;

		void resize(uint32_t width, uint32_t height);

		static void pollEvents();
		void        close();
		bool        shouldClose() const;

	   public:
		uint32_t getWidth() const { return m_Width; }

		std::string getTitle() const { return m_Title; }

		uint32_t getHeight() const { return m_Height; }

		NativeWindowHandle getNativeWindowHandle() const;

	   private:
		static void resizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* m_Window = nullptr;

		uint32_t    m_Width  = 0;
		uint32_t    m_Height = 0;
		std::string m_Title  = "";
	};

}  // namespace Synergon::Window
