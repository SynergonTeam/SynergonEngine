#include "TestClasses.hpp"
#include "Synergon/Window/Window.hpp"

TEST_P(WindowTest, WindowInitialization) {
	auto [width, height, fullscreen, resizable] = GetParam();

	Synergon::Window::WindowDescriptor descriptor;
	descriptor.title      = "Test Window";
	descriptor.width      = width;
	descriptor.height     = height;
	descriptor.fullscreen = fullscreen;
	descriptor.resizable  = resizable;

	Synergon::Window::Window window(descriptor);

	ASSERT_NE(window.getNativeWindowHandle(), nullptr);
}

INSTANTIATE_TEST_SUITE_P(
    WindowConfigurations,
    WindowTest,
    ::testing::Values(
        std::make_tuple(800, 600, false, false),
        std::make_tuple(1024, 768, false, true),
        std::make_tuple(1920, 1080, true, false),
        std::make_tuple(2560, 1440, true, true)));