cmake_minimum_required(VERSION 3.22)
project(chapter-2)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR ./resources/include)
set(SDL2_LIB_DIR ./resources/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(chapter-2 src/main.cpp src/Game.h src/Game.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
