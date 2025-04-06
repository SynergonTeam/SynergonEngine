# Build Instructions for SynergonEngine

## Prerequisites

1. **CMake**: Version 3.20 or higher.
2. **C/C++ compiler**: Any modern c/c++ compiler that supports c++20
3. **Vulkan SDK**: API Version 1.3
4. **vcpkg**: Ensure `VCPKG_CMAKE` environment variable is set to the path of `vcpkg.cmake`.
5. **Compiler**:
    - **Windows**: Visual Studio (MSVC), GCC, CLANG
    - **Linux**: GCC, Clang
    - **Unix**: Makefiles, Ninja

> **Llvm with MingW**: if you installed mingw with llvm and added them to the path togather, their linker (ld) will conflict. Thus, either one of them may not be able to configure and compile the project!

## Setting Up vcpkg

1. Create the vcpkg toolchain file for CMake:

    ```sh
    vcpkg integrate install
    ```

2. Set the `VCPKG_CMAKE` environment variable:
    - **Windows**:
        ```bat
        SETX VCPKG_CMAKE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
        ```
    - **Linux**:
        ```sh
        export VCPKG_CMAKE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
        ```

## Building the Project

### CMakePresets.json

1. Open a terminal and navigate to the project directory.
2. List configure and build presets:
    ```sh
    cmake --list-presets configure
    cmake --list-presets build
    ```
3. Configure the project using one of the configure presets:
    ```sh
    cmake --preset vs2022-shared
    ```
4. Build the project using one of the build presets:
    ```sh
    cmake --build --preset vs2022-shared-relwithdebinfo
    ```
5. Or use workflows
    1. List available workflows:
    ```sh
    cmake --list-presets workflow
    ```
    2. Use the workflow to configure and build at once:
    ```sh
     cmake --workflow --preset ninja-clang-shared-release
    ```

### Windows (MSVC)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```bat
    mkdir Build
    cd Build
    ```
3. Configure the project using CMake:
    ```bat
    cmake ..
    ```
4. Build the project:
    ```bat
    cmake --build . --config Release
    ```

### Windows (NO MSVC)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```bat
    mkdir Build
    cd Build
    ```
3. Configure the project using CMake (Ninja/Unix Makefiles and clang/g++):
    ```bat
    cmake -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=clang ..
    ```
4. Build the project:
    ```bat
     ninja
    ```

### Linux (GCC)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```
3. Configure the project using CMake:
    ```sh
    cmake ..
    ```
4. Build the project:
    ```sh
    make
    ```

### Linux (Clang)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```
3. Configure the project using CMake:
    ```sh
    cmake -DCMAKE_CXX_COMPILER=clang ..
    ```
4. Build the project:
    ```sh
    make
    ```

### Unix (Makefiles)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```
3. Configure the project using CMake:
    ```sh
    cmake -G "Unix Makefiles" ..
    ```
4. Build the project:
    ```sh
    make
    ```

### Unix (Ninja)

1. Open a terminal and navigate to the project directory.
2. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```
3. Configure the project using CMake:
    ```sh
    cmake -G "Ninja" ..
    ```
4. Build the project:
    ```sh
    ninja
    ```

## Build Options

### Common

-   `CMAKE_BUILD_TYPE`: Specify Build type of either Debug or Release with non-MSVC compilers (default: Debug)
-   `BUILD_SHARED_LIBS`: Build shared libraries (default: OFF)
-   `WITHOUT_SAMPLES`: Build without samples (default: OFF)
-   `WIN32_RELEASE_MODE_NO_CONSOLE`: Build win32 samples without console on release mode (default: OFF)

To enable these options, pass them to the `cmake` command:

```sh
cmake -DBUILD_SHARED_LIBS=ON -DWITHOUT_SAMPLES=ON -DWIN32_RELEASE_MODE_NO_CONSOLE=ON ..
```
