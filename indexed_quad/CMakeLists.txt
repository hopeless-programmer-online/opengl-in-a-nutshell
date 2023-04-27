project(indexed_quad
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(indexed_quad "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(indexed_quad PRIVATE
    glm
    glfw
    libglew_static
)
