project(depth_test
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(depth_test "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(depth_test PUBLIC
    "${libpng_SOURCE_DIR}" "${libpng_BINARY_DIR}"
)
target_link_libraries(depth_test PUBLIC
    glm
    glfw
    libglew_static
    png_static
    assimp
    zlibstatic
)
