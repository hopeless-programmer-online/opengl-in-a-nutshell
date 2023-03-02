# OpenGL in a nutshell

- `cmake -S . -B _build` to generate.
- `cmake --build _build` to build.
- `_build\hello_triangle\hello_triangle.exe` to run `hello_triangle`.

## Prerequisites

- [CMake 3.25+](https://cmake.org/download).
- [C++20](https://en.wikipedia.org/wiki/C++20) compatible compiler.

## Dependencies

- [C++20](https://en.wikipedia.org/wiki/C++20) compatible compiler.
- [GLFW](https://www.glfw.org/).
- [GLEW](https://github.com/Perlmint/glew-cmake).
- [GLM](https://github.com/g-truc/glm).

## Known issues

- Use `-G "MinGW Makefiles"` with `cmake -S . -B _build` to generate project for MinGW.
