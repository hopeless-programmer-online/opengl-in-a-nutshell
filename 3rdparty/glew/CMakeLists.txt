include(FetchContent)

message(STATUS "Fetching GLEW...")

set(glew-cmake_BUILD_SHARED          OFF CACHE INTERNAL "Build the shared glew library")
set(glew-cmake_BUILD_STATIC          ON  CACHE INTERNAL "Build the static glew library")
set(USE_GLU                          OFF CACHE INTERNAL "Use GLU")
set(GLEW_OSMESA                      OFF CACHE INTERNAL "Off-screen Mesa mode")
set(PKG_CONFIG_REPRESENTATIVE_TARGET OFF CACHE INTERNAL "Generate pc file for specified target as glew. libglew_static|libglew_shared")
set(ONLY_LIBS                        ON  CACHE INTERNAL "Do not build executables")

FetchContent_Declare(
    glew
    GIT_REPOSITORY    "https://github.com/Perlmint/glew-cmake.git"
    GIT_TAG           "glew-cmake-2.2.0"
    FIND_PACKAGE_ARGS NAMES GLEW
)

FetchContent_MakeAvailable(glew)
