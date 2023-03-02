project(colored_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(colored_triangle "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(colored_triangle PRIVATE
    glm
    glfw
    libglew_static
)
