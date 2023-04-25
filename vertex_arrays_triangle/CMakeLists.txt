project(vertex_arrays_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(vertex_arrays_triangle "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(vertex_arrays_triangle PRIVATE
    glfw
    libglew_static
)
