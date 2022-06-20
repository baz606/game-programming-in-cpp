cmake_minimum_required(VERSION 3.22)
project(chapter-1)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR ./SDL/include)
set(SDL2_LIB_DIR ./SDL/build/Release)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(chapter-1 main.cpp Game.h Game.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
