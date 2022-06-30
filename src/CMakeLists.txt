cmake_minimum_required(VERSION 3.22)
project(leard_sdl_chapter_2)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR D:/SDL/include)
set(SDL2_LIB_DIR D:/SDL/lib/x64)

set(SDL2_INCLUDE_IMAGE_DIR D:/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
set(SDL2_LIB_IMAGE_DIR D:/SDL2_image-2.0.5/x86_64-w64-mingw32/bin)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_IMAGE_DIR})

link_directories(${SDL2_LIB_DIR})
link_directories(${SDL2_LIB_IMAGE_DIR})

add_executable(leard_sdl_chapter_2 main.cpp Actor.cpp Actor.h Component.cpp Component.h Game.cpp Game.h SpriteComponent.cpp SpriteComponent.h Math.cpp Math.h AnimSpriteComponent.cpp AnimSpriteComponent.h BGSpriteComponent.cpp BGSpriteComponent.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)