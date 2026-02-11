cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TableTennis)
set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
set(SDLTTF_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Shared source files
file(GLOB_RECURSE SharedFiles "src/shared/*")

# Add source files
file(GLOB_RECURSE SrcFiles "src/*")
add_executable(TableTennis main.cpp ${SrcFiles} ${SharedFiles})

# Copy assets
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# Add libraries
include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
        GIT_TAG        release-3.4.0
)

FetchContent_Declare(
        SDL3_IMAGE
        GIT_REPOSITORY git@github.com:libsdl-org/SDL_image.git
        GIT_TAG        release-3.4.0
)

FetchContent_Declare(
        SDL3_TTF
        GIT_REPOSITORY git@github.com:libsdl-org/SDL_ttf.git
        GIT_TAG        release-3.2.2
)

FetchContent_Declare(
        SDL3_MIXER
        GIT_REPOSITORY git@github.com:libsdl-org/SDL_mixer.git
        GIT_TAG        prerelease-3.1.2
)
FetchContent_MakeAvailable(SDL3 SDL3_IMAGE SDL3_TTF SDL3_MIXER)

target_link_libraries(TableTennis PUBLIC
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
)

# Server code
add_executable(Server server.cpp ${SharedFiles})
target_link_libraries(Server PUBLIC)