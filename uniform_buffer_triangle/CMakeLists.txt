project(uniform_buffer_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(uniform_buffer_triangle "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(uniform_buffer_triangle PRIVATE
    glfw
    libglew_static
)
