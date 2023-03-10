project(matrix2d
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(matrix2d "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(matrix2d PUBLIC
    "${libpng_SOURCE_DIR}" "${libpng_BINARY_DIR}"
)
target_link_libraries(matrix2d PUBLIC
    glm
    glfw
    libglew_static
    png_static
    zlibstatic
)
