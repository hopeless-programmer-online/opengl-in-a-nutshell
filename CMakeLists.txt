cmake_minimum_required(VERSION 3.25)

project(opengl_in_a_nutshell
    VERSION 1.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(3rdparty)

add_subdirectory(window)
add_subdirectory(clear_screen)
add_subdirectory(hello_triangle)
add_subdirectory(uniform_triangle)
add_subdirectory(uniform_buffer_triangle)
add_subdirectory(vertex_arrays_triangle)
add_subdirectory(colored_triangle)
add_subdirectory(indexed_quad)
add_subdirectory(texture)
add_subdirectory(load_texture)
add_subdirectory(matrix2d)
add_subdirectory(matrix3d)
add_subdirectory(perspective)
add_subdirectory(depth_test)
