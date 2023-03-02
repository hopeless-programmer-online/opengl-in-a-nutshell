include(FetchContent)

message(STATUS "Fetching LIBPNG...")

# find_package(ZLIB REQUIRED)

set(BUILD_SHARED_LIBS          OFF CACHE INTERNAL "Build shared libraries")
set(PNG_SHARED                 OFF CACHE INTERNAL "Build libpng as a shared lib")
set(PNG_STATIC                 ON  CACHE INTERNAL "Build libpng as a static lib")
set(PNG_FRAMEWORK              OFF CACHE INTERNAL "Build libpng as a Mac OS X framework")
set(PNG_EXECUTABLES            OFF CACHE INTERNAL "Build libpng executables")
set(PNG_TESTS                  OFF CACHE INTERNAL "Build libpng tests")
set(PNG_DEBUG                  OFF CACHE INTERNAL "Enable debug output")
set(PNG_HARDWARE_OPTIMIZATIONS ON  CACHE INTERNAL "Enable hardware optimizations")

set(BUILD_TESTING           OFF CACHE INTERNAL "")
set(SKIP_INSTALL_LIBRARIES  ON  CACHE INTERNAL "")
set(SKIP_INSTALL_EXPORT     ON  CACHE INTERNAL "")
set(ZLIB_INCLUDE_DIRS      "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")

FetchContent_Declare(
    libpng
    GIT_REPOSITORY    "https://github.com/glennrp/libpng.git"
    GIT_TAG           "v1.6.39"
    FIND_PACKAGE_ARGS NAMES PNG
)
FetchContent_MakeAvailable(libpng)
