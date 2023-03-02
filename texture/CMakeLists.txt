project(texture
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(texture "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(texture PRIVATE
    "${glew_SOURCE_DIR}/include"
    "${glm_SOURCE_DIR}"
)
target_link_libraries(texture PRIVATE
    glfw
    libglew_static
)
