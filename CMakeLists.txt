cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
project(TableTennis)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_mixer REQUIRED)

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Add source files
add_executable(
        TableTennis main.cpp
        src/render/renderwindow.cpp src/render/renderwindow.h src/utility/vector3.cpp src/utility/vector3.h src/utility/mathutil.cpp src/utility/mathutil.h src/gameplay/clickmanager.cpp src/gameplay/clickmanager.h src/entity/component.h src/entity/component.cpp src/entity/components/spriterenderer.h src/entity/components/spriterenderer.cpp src/entity/entity.cpp src/entity/entity.h)

# Link libraries
target_link_libraries(
        TableTennis
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
