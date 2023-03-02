project(hello_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(hello_triangle "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(hello_triangle PRIVATE
    "${glm_SOURCE_DIR}"
)
target_link_libraries(hello_triangle PRIVATE
    glfw
    libglew_static
)
