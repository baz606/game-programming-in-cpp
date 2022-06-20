# Game programming in C++
This repository contains my progress from Game Programming in C++ from Sanjay Madhav's book

The chapter codes are in separate branches. Each chapter builds upon the previous chapter's code

## Build instructions
Use the following statements and instructions to correctly compile and run this game on **Windows 10**:
1) `git clone --recursive git@github.com:baz606/game-programming-in-cpp.git`
2) `cd SDL/ && mkdir build`
3) `cd build && cmake.exe ..`
4) Open SDL2.sln in visual studio. I used visual studio 2019
5) Change build to **Release**
6) Select _Build_ > _Build solution_
7) Copy SDL2.dll from SDL/build/Release directory to wherever your .exe file is generated when you compile this branch's code. I used CLion to compile and run my program so I had to copy the SDL2.dll to _cmake-build-debug_ directory
8) Run the .exe file and enjoy!
