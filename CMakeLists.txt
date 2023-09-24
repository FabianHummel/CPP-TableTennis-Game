cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(TableTennis)

# Shared source files
file(GLOB_RECURSE SharedFiles "src/shared/*")

# Add source files
file(GLOB_RECURSE SrcFiles "src/*")
add_executable(TableTennis main.cpp ${SrcFiles} ${SharedFiles})

# Copy assets
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# Add libraries
find_package(PkgConfig REQUIRED)
include(FetchContent)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_NET REQUIRED IMPORTED_TARGET SDL2_net)
pkg_check_modules(SDL2_GFX REQUIRED IMPORTED_TARGET SDL2_gfx)
pkg_check_modules(LIBENET REQUIRED IMPORTED_TARGET libenet)

target_link_libraries(TableTennis PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_IMAGE
    PkgConfig::SDL2_TTF
    PkgConfig::SDL2_MIXER
    PkgConfig::SDL2_NET
    PkgConfig::SDL2_GFX
    PkgConfig::LIBENET
)

# Server code
add_executable(Server server.cpp ${SharedFiles})
target_link_libraries(Server PUBLIC
    PkgConfig::LIBENET
)