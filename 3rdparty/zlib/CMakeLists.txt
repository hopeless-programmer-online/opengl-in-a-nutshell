include(FetchContent)

message(STATUS "Fetching ZLIB...")

FetchContent_Declare(
    zlib
    GIT_REPOSITORY "https://github.com/madler/zlib.git"
)

FetchContent_MakeAvailable(zlib)
