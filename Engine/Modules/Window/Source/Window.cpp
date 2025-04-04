#include "Synergon/Window/Window.hpp"

namespace Synergon::Window {

	Window::Window(const WindowDescriptor& descriptor) {
		m_Width  = descriptor.width;
		m_Height = descriptor.height;
		m_Title  = descriptor.title;

		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, descriptor.resizable);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

		//
		// TODO: Handle icon, rn we can't load images so I'll skip it
		//

		if (descriptor.fullscreen) {
			glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, m_Width, m_Height, GLFW_DONT_CARE);
		}

		glfwSetFramebufferSizeCallback(m_Window, Window::resizeCallback);

		glfwSetWindowUserPointer(m_Window, (void*)this);
	}

	Window::Window(Window&& other) noexcept {
		m_Window       = other.m_Window;
		other.m_Window = nullptr;

		m_Width  = other.m_Width;
		m_Height = other.m_Height;
		m_Title  = std::move(other.m_Title);

		glfwSetWindowUserPointer(m_Window, (void*)this);
	}

	Window& Window::operator=(Window&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		m_Window       = other.m_Window;
		other.m_Window = nullptr;

		m_Width  = other.m_Width;
		m_Height = other.m_Height;
		m_Title  = std::move(other.m_Title);

		glfwSetWindowUserPointer(m_Window, (void*)this);

		return *this;
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::close() {
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::resizeCallback(GLFWwindow* window, int width, int height) {
		Window* userPointer   = static_cast<Window*>(glfwGetWindowUserPointer(window));
		userPointer->m_Width  = width;
		userPointer->m_Height = height;
	}

	void Window::resize(uint32_t width, uint32_t height) {
		m_Width  = width;
		m_Height = height;
		glfwSetWindowSize(m_Window, m_Width, m_Height);
	}

}  // namespace Synergon::Core