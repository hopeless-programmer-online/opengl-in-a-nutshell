include(FetchContent)

message(STATUS "Fetching GLEW...")

FetchContent_Declare(
    glew
    GIT_REPOSITORY "https://github.com/Perlmint/glew-cmake.git"
)

set(glew-cmake_BUILD_SHARED OFF)
set(glew-cmake_BUILD_STATIC ON)
set(ONLY_LIBS ON)

FetchContent_MakeAvailable(glew)
