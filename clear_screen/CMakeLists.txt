project(clear_screen
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(clear_screen "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(clear_screen PRIVATE
    glfw
    libglew_static
)
