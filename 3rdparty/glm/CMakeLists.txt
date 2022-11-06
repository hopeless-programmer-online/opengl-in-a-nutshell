include(FetchContent)

message(STATUS "Fetching GLM...")

FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
)

FetchContent_MakeAvailable(glm)
