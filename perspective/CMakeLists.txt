project(perspective
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(perspective "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(perspective PUBLIC
    "${libpng_SOURCE_DIR}" "${libpng_BINARY_DIR}"
)
target_link_libraries(perspective PUBLIC
    glm
    glfw
    libglew_static
    png_static
    zlibstatic
)
