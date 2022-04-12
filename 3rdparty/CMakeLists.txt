include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
)

add_subdirectory(glfw)
