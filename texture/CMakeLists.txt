project(texture
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(texture "src/main.cpp")

target_include_directories(texture PRIVATE
    "${GLFW_SOURCE_DIR}/include"
    "${glew_SOURCE_DIR}/include"
    "${glm_SOURCE_DIR}"
)
target_link_libraries(texture PRIVATE
    glfw
    libglew_static
)
