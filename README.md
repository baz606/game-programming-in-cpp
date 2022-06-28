# Game programming in C++
This repository contains my progress from Game Programming in C++ from Sanjay Madhav's book

The chapter code are in separate branches. Each chapter usually builds upon the previous chapter

## Build instructions
Use the following statements and instructions to correctly compile and run this game on **Windows 10**.</br> I am
assuming building on other platforms will be similar as long as you have cmake installed. I used CLion to compile and 
run this project, but you can also use _cmake_ and _visual studio_ to do the same.</br>

1) Clone this repo using: `git clone git@github.com:baz606/game-programming-in-cpp.git`
2) _Extract here_ the **SDL** library in **resources** directory. You can also build SDL on your own or grab a binary
   that suits your operating system from the SDL website: https://www.libsdl.org/download-2.0.php

### Next, lets build the game:
3) Go back to root directory of this project
4) Run `mkdir build && cd build && cmake.exe ..`
5) Open **chapter-1.sln** in visual studio. I used visual studio 2019
6) Change build to **Release**
7) Alternatively, you can automatically use CLion to compile and run the code using CMakeLists.txt file.
8) Now, copy **SDL2.dll** from **./resources/lib/x64** directory to wherever your .exe file is generated when you 
   compile this branch's code. I used CLion to compile and run my program, so I had to copy the SDL2.dll to
   _cmake-build-debug_ directory
9) Run the .exe file and enjoy!
