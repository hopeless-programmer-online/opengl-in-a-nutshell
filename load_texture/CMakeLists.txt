project(load_texture
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(load_texture "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_include_directories(load_texture PUBLIC
    "${libpng_SOURCE_DIR}" "${libpng_BINARY_DIR}"
)
target_link_libraries(load_texture PUBLIC
    glm
    glfw
    libglew_static
    png_static
    zlibstatic
)
