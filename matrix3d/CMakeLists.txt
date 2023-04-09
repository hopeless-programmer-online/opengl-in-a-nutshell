project(matrix3d
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(matrix3d "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(matrix3d PUBLIC
    "${libpng_SOURCE_DIR}" "${libpng_BINARY_DIR}"
)
target_link_libraries(matrix3d PUBLIC
    glm
    glfw
    libglew_static
    png_static
    zlibstatic
)
