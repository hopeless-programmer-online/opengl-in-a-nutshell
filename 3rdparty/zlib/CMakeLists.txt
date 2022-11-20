include(FetchContent)

message(STATUS "Fetching ZLIB...")

FetchContent_Declare(
    zlib
    GIT_REPOSITORY "https://github.com/hopeless-programmer-online/zlib.git"
    GIT_TAG        "test_option"
    FIND_PACKAGE_ARGS
)

set(ZLIB_BUILD_TESTS OFF)

FetchContent_MakeAvailable(zlib)
