include(FetchContent)

message(STATUS "Fetching GLFW...")

set(BUILD_SHARED_LIBS   OFF CACHE INTERNAL "Build shared libraries")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS    OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS     OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL        OFF CACHE INTERNAL "Generate installation target")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY     "https://github.com/glfw/glfw.git"
    GIT_TAG            "3.3.8"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(glfw)
