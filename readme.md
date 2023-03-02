# OpenGL in a nutshell

## Quick start

To build all projects from source with CMake run:

- `cmake -S . -B _build` to generate. See [this](#known-issues) for possible issues.
- `cmake --build _build` to build.
- Explore `_build` folder for executables (e.g. `_build\load_texture\load_texture.exe`).

## Prerequisites

The following dependencies must be installed manually:

- [CMake 3.25+](https://cmake.org/download).
- [C++20](https://en.wikipedia.org/wiki/C++20) compatible compiler.

## Dependencies

The following dependencies will be automatically installed during generation:

- [C++20](https://en.wikipedia.org/wiki/C++20) compatible compiler.
- [GLFW](https://www.glfw.org/).
- [GLEW](https://github.com/Perlmint/glew-cmake).
- [GLM](https://github.com/g-truc/glm).
- [ZLIB](https://github.com/madler/zlib) (modified).
- [LibPNG](https://github.com/glennrp/libpng).

These dependencies installed locally and will not change any global packages/configurations.
You can find them in build folder (`_build`).

## Known issues

- Use `-G "MinGW Makefiles"` with `cmake -S . -B _build` to generate project for MinGW.
