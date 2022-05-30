project(window
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(window "src/main.cpp")

target_include_directories(window PRIVATE
    "${GLFW_SOURCE_DIR}/include"
)
target_link_libraries(window PRIVATE
    glfw
)
