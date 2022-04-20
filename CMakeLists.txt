cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
project(TableTennis)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Add source files
add_executable(
        TableTennis main.cpp
        src/render/renderwindow.cpp src/render/renderwindow.h src/ballentity.cpp src/ballentity.h src/entitybase.cpp src/entitybase.h src/shadowentity.cpp src/shadowentity.h src/utility/vector3.cpp src/utility/vector3.h src/utility/mathutil.cpp src/utility/mathutil.h src/render/rendermanager.cpp src/render/rendermanager.h src/render/rendertarget.cpp src/render/rendertarget.h)

# Link libraries
target_link_libraries(
        TableTennis
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)