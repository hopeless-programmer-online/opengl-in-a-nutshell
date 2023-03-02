include(FetchContent)

message(STATUS "Fetching GLM...")

FetchContent_Declare(
    glm
    GIT_REPOSITORY    "https://github.com/g-truc/glm"
    GIT_TAG           "0.9.9.8"
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(glm)
