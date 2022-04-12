project(hello_triangle
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(hello_triangle "src/main.cpp")

target_include_directories(hello_triangle PRIVATE
    "${GLFW_SOURCE_DIR}/include"
    "${glew_SOURCE_DIR}/include"
)
target_link_libraries(hello_triangle PRIVATE
    glfw
    libglew_static
)
