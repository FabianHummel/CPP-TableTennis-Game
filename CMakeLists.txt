cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
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
        src/render/renderwindow.cpp src/render/renderwindow.h src/utility/vector3int.cpp src/utility/vector3int.h src/utility/mathutil.cpp src/utility/mathutil.h src/gameplay/clickmanager.cpp src/gameplay/clickmanager.h src/gameplay/components/spriterenderer.h src/gameplay/components/spriterenderer.cpp src/entity/entity.cpp src/entity/entity.h src/gameplay/components/ballmovement.h src/gameplay/components/ballmovement.cpp src/entity/entitymanager.cpp src/entity/entitymanager.h src/gameplay/components/shadowtransformer.cpp src/gameplay/components/shadowtransformer.h src/gameplay/components/transform.cpp src/gameplay/components/transform.h src/gameplay/component.h src/gameplay/component.cpp src/utility/vector2int.cpp src/utility/vector2int.h src/utility/vector3.cpp src/utility/vector3.h src/gameplay/components/gamemanager.cpp src/gameplay/components/gamemanager.h)

# Link libraries
target_link_libraries(
        TableTennis
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
