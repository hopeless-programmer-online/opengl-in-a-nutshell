project(colored_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(colored_triangle "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(colored_triangle PRIVATE
    "${glm_SOURCE_DIR}"
)
target_link_libraries(colored_triangle PRIVATE
    glfw
    libglew_static
)
