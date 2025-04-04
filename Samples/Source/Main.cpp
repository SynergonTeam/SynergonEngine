#include "Synergon/Engine.hpp"
#include <Synergon/Samples.hpp>

#include "Synergon/Window/Window.hpp"

int main(int argc, char **argv) {
	Synergon::EngineTempFunction();
	Synergon::SamplesTempFunction();

	// Temporary test code
	{
		Synergon::Window::WindowDescriptor descriptor;
		descriptor.title      = "Test Window";
		descriptor.width      = 800;
		descriptor.height     = 800;
		descriptor.fullscreen = false;
		descriptor.resizable  = true;

		Synergon::Window::Window window(descriptor);

		while (!window.shouldClose()) {
			window.pollEvents();
		}
	}

	return 0;
}

#if (defined(_WIN32) || defined(_WIN64)) && defined(_MSC_VER) && defined(SYNERGON_ENGINE_BUILD_TYPE_RELEASE)
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	include <cstdlib>

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow) {
	return main(__argc, __argv);
}
#endif
