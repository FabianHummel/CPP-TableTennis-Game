cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
project(TableTennis)

# Add source files
add_executable(
        TableTennis main.cpp
        src/render/renderwindow.cpp src/render/renderwindow.h src/utility/vector3int.cpp src/utility/vector3int.h src/utility/mathutil.cpp src/utility/mathutil.h src/gameplay/components/spriterenderer.h src/gameplay/components/spriterenderer.cpp src/entity/entity.cpp src/entity/entity.h src/gameplay/components/ballmovement.h src/gameplay/components/ballmovement.cpp src/entity/entitymanager.cpp src/entity/entitymanager.h src/gameplay/components/shadowtransformer.cpp src/gameplay/components/shadowtransformer.h src/gameplay/components/transform.cpp src/gameplay/components/transform.h src/gameplay/component.h src/gameplay/component.cpp src/utility/vector2int.cpp src/utility/vector2int.h src/utility/vector3.cpp src/utility/vector3.h src/gameplay/components/gamemanager.cpp src/gameplay/components/gamemanager.h src/gameplay/components/clickmanager.cpp src/gameplay/components/clickmanager.h src/gameplay/components/powerbar.cpp src/gameplay/components/powerbar.h src/sound/soundmanager.cpp src/sound/soundmanager.h)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
#find_package(SDL2_ttf REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
find_package(SDL2_mixer REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)

# Copy assets
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})