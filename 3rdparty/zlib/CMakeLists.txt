include(FetchContent)

message(STATUS "Fetching ZLIB...")

set(BUILD_SHARED_LIBS OFF)
set(ZLIB_BUILD_TESTS OFF)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY "https://github.com/hopeless-programmer-online/zlib.git"
    GIT_TAG        "test_option"
    FIND_PACKAGE_ARGS NAMES ZLIB
)
FetchContent_MakeAvailable(zlib)
