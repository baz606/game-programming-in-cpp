# Game programming in C++
This repository contains my progress from Game Programming in C++ from Sanjay Madhav's book

The chapter code are in separate branches. Each chapter usually builds upon the previous chapter

## Build instructions
Use the following statements and instructions to correctly compile and run this game on **Windows 10**.</br> I am
assuming building on other platforms will be similar as long as you have cmake installed. I used CLion to compile and 
run this project, but you can also use _cmake_ and _visual studio_ to do the same.</br>

First, we build the SDL library, if you don't have it already setup on your computer:
1) `git clone --recursive git@github.com:baz606/game-programming-in-cpp.git`
2) `cd SDL && mkdir build`
3) `cd build && cmake.exe ..`
4) Open **SDL2.sln** in visual studio. I used visual studio 2019
5) Change build to **Release**
6) Select _Build_ > _Build solution_. This will generate **SDL2.dll** under SDL/build/Release. We will add
   this dll later once we compile and link the source code of this branch.

### Next, lets build the game:
7) `cd` back to root directory of this project
8) `mkdir build && cd build && cmake.exe ..`
9) Open **chapter-1.sln** in visual studio. I used visual studio 2019
10) Change build to **Release**
11) Now, copy **SDL2.dll** from **step 6** SDL/build/Release directory to wherever your .exe file is generated when you 
    compile this branch's code. I used CLion to compile and run my program, so I had to copy the SDL2.dll to
    _cmake-build-debug_ directory
12) Run the .exe file and enjoy!
