include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
)

add_subdirectory(glfw)

FetchContent_Declare(
    glew
    GIT_REPOSITORY "https://github.com/Perlmint/glew-cmake.git"
)

add_subdirectory(glew)
