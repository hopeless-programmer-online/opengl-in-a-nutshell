include(FetchContent)

message(STATUS "Fetching LIBPNG...")

FetchContent_Declare(
    libpng
    GIT_REPOSITORY "https://github.com/maisvendoo/libpng-cmake.git"
)

set(PNG_BUILD_ZLIB OFF)
set(ZLIB_LIBRARY zlib)
set(ZLIB_INCLUDE_DIR "${zlib_SOURCE_DIR}" "${zlib_BINARY_DIR}")

set(PNG_SHARED OFF)
set(PNG_STATIC ON)
set(PNG_TESTS OFF)
set(PNG_HARDWARE_OPTIMIZATIONS ON)

FetchContent_MakeAvailable(libpng)
