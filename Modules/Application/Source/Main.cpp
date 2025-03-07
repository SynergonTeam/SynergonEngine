#include <Synergon/Samples.hpp>

int main(int argc, char **argv) {
    Synergon::ThirdPartyTempFunction();
    Synergon::EngineTempFunction();
    Synergon::SamplesTempFunction();

    return 0;
}

#if (defined(_WIN32) || defined(_WIN64)) && defined(_MSC_VER) && defined(SYNERGON_ENGINE_BUILD_TYPE_RELEASE)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdlib>

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow) {
    return main(__argc, __argv);
}
#endif
