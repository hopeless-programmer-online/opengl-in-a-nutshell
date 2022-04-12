message(STATUS "Fetching GLEW...")

set(glew-cmake_BUILD_SHARED OFF)
set(glew-cmake_BUILD_STATIC ON)
set(ONLY_LIBS ON)

FetchContent_MakeAvailable(glew)
