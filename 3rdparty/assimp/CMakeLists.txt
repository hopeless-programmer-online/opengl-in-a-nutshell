include(FetchContent)

message(STATUS "Fetching ASSIMP...")

set(BUILD_SHARED_LIBS           OFF CACHE INTERNAL "Build shared libraries")
set(ASSIMP_BUILD_TESTS          OFF CACHE INTERNAL "If the test suite for Assimp is built in addition to the library.")
set(ASSIMP_INSTALL              OFF CACHE INTERNAL "Disable this if you want to use assimp as a submodule.")
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE INTERNAL "Inject debug postfix in .a/.so/.dll lib names")
set(ASSIMP_BUILD_ZLIB           OFF CACHE INTERNAL "Build your zlib")
set(ASSIMP_INSTALL_PDB          OFF CACHE INTERNAL "Install MSVC debug files.")
set(USE_STATIC_CRT              OFF CACHE INTERNAL "Link against the static runtime libraries.")
set(ASSIMP_BUILD_ASSIMP_VIEW    OFF CACHE INTERNAL "If the Assimp view tool is built. (requires DirectX)")

set(BUILD_TESTING           OFF CACHE INTERNAL "")
set(SKIP_INSTALL_LIBRARIES  ON  CACHE INTERNAL "")
set(SKIP_INSTALL_EXPORT     ON  CACHE INTERNAL "")
set(ZLIB_INCLUDE_DIRS       "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")
set(ZLIB_INCLUDE_DIR        "${zlib_SOURCE_DIR};${zlib_BINARY_DIR}")

FetchContent_Declare(
    assimp
    GIT_REPOSITORY    "https://github.com/assimp/assimp.git"
    GIT_TAG           "v5.4.0"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(assimp)
