# Game programming in C++
This repository contains my progress from Game Programming in C++ from Sanjay Madhav's book

The chapter code are in separate branches. Each chapter usually builds upon the previous chapter

## Build instructions
Use the following statements and instructions to correctly compile and run this game on **Windows 10**.</br> I am
assuming building on other platforms will be similar as long as you have cmake installed. I used CLion to compile and 
run this project, but you can also use _cmake_ and _visual studio_ to do the same.</br>

1) Clone this repo using: `git clone git@github.com:baz606/game-programming-in-cpp.git`
2) _Extract to "SDL2..."_ the **SDL** library in **resources** directory. You can also build SDL on your own or grab a 
   binary that suits your operating system from the SDL website: https://www.libsdl.org/download-2.0.php
3) Repeat step 2 for SDL2_image library in resources directory.

### Next, lets build the game:
4) Go back to root directory of this project
5) Run `mkdir build && cd build && cmake.exe ..`
6) Open **chapter-1.sln** in visual studio. I used visual studio 2019
7) Change build to **Release**
8) Now, copy **SDL2.dll** from **./resources/SDL2-2.0.22/lib/x64** directory and **SDL2_image.dll** from
   **./resources/SDL2_image-2.0.5/lib/x64** directory to wherever your .exe file is generated when you compile this
   branch's code. I used CLion to compile and run my program, so I had to copy the SDL2.dll and SDL2_image.dll to 
   _cmake-build-debug_ directory
9) Alternatively, you can automatically use CLion to compile and run the code using CMakeLists.txt file.
10) Run the .exe file and enjoy!
