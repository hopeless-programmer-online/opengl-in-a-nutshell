project(window
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(window "src/main.cpp")
target_compile_features(window PRIVATE cxx_std_20)
target_link_libraries(window PRIVATE
    glfw
)
