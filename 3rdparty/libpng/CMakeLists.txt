include(FetchContent)

message(STATUS "Fetching LIBPNG...")

find_package(ZLIB REQUIRED)

set(ZLIB_INCLUDE_DIRS "${zlib_SOURCE_DIR}" "${zlib_BINARY_DIR}")

set(BUILD_SHARED_LIBS OFF)
set(PNG_SHARED OFF)
set(PNG_STATIC ON)
set(PNG_TESTS OFF)
# set(PNG_HARDWARE_OPTIMIZATIONS ON)

FetchContent_Declare(
    libpng
    GIT_REPOSITORY "https://github.com/glennrp/libpng.git"
)
FetchContent_MakeAvailable(libpng)
