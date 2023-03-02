include(FetchContent)

message(STATUS "Fetching ZLIB...")

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build shared libraries")
set(ZLIB_BUILD_TESTS  OFF CACHE INTERNAL "Build ZLIB tests")

FetchContent_Declare(
    zlib
    GIT_REPOSITORY    "https://github.com/hopeless-programmer-online/zlib.git"
    GIT_TAG           "test_option"
    FIND_PACKAGE_ARGS NAMES ZLIB
)
FetchContent_MakeAvailable(zlib)
