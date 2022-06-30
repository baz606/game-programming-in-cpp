cmake_minimum_required(VERSION 3.22)
project(chapter-2)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR ./resources/SDL2-2.0.22/include)
set(SDL2_LIB_DIR ./resources/SDL2-2.0.22/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR ./resources/SDL2_image-2.0.5/include)
set(SDL2_IMAGE_LIB_DIR ./resources/SDL2_image-2.0.5/lib/x64)

file(GLOB SOURCES
  src/*.h
  src/*.cpp
  )

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB_DIR})

add_executable(chapter-2 ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)
