include(FetchContent)

message(STATUS "Fetching LIBPNG...")

find_package(ZLIB REQUIRED)

set(ZLIB_INCLUDE_DIRS "${zlib_SOURCE_DIR}" "${zlib_BINARY_DIR}")

set(BUILD_SHARED_LIBS OFF)
set(EVENT__DISABLE_TESTS ON)
set(PNG_SHARED OFF CACHE INTERNAL "Build shared lib")
set(PNG_STATIC ON CACHE INTERNAL "Build static lib")
set(PNG_EXECUTABLES OFF CACHE INTERNAL "Build libpng executables")
set(PNG_TESTS OFF CACHE INTERNAL "Build libpng tests")
set(PNG_HARDWARE_OPTIMIZATIONS ON CACHE INTERNAL "Enable hardware optimizations")

FetchContent_Declare(
    libpng
    GIT_REPOSITORY "https://github.com/glennrp/libpng.git"
)
FetchContent_MakeAvailable(libpng)
