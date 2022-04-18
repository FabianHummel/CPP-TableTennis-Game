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
        src/renderwindow.cpp src/renderwindow.h src/ballentity.cpp src/ballentity.h src/entitybase.cpp src/entitybase.h src/shadowentity.cpp src/shadowentity.h src/utility/vector3.cpp src/utility/vector3.h src/utility/mathutil.cpp src/utility/mathutil.h src/rendermanager.cpp src/rendermanager.h src/rendertarget.cpp src/rendertarget.h)

# Link libraries
target_link_libraries(
        TableTennis
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)