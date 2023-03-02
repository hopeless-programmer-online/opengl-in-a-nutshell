project(texture
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(texture "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(texture PRIVATE
    glm
    glfw
    libglew_static
)
