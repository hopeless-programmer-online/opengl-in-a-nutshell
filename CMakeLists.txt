cmake_minimum_required(VERSION 3.0)

project(opengl_in_a_nutshell
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(3rdparty)

add_subdirectory(hello_triangle)
add_subdirectory(colored_triangle)
add_subdirectory(texture)
