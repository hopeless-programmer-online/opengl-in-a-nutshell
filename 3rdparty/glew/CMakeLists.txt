include(FetchContent)

message(STATUS "Fetching GLEW...")

set(BUILD_SHARED_LIBS OFF)
set(glew-cmake_BUILD_SHARED OFF CACHE INTERNAL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC ON CACHE INTERNAL "Build the static glew library")
set(ONLY_LIBS OFF CACHE INTERNAL "Do not build executables")

FetchContent_Declare(
    glew
    GIT_REPOSITORY "https://github.com/Perlmint/glew-cmake.git"
)
FetchContent_MakeAvailable(glew)
