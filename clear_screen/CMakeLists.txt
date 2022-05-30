project(clear_screen
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(clear_screen "src/main.cpp")

target_include_directories(clear_screen PRIVATE
    "${GLFW_SOURCE_DIR}/include"
    "${glew_SOURCE_DIR}/include"
)
target_link_libraries(clear_screen PRIVATE
    glfw
    libglew_static
)
