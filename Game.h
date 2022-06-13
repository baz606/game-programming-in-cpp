//
// Created by baz606 on 6/9/2022.
//

/**
  Copyright (c) 2017, Sanjay Madhav
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LEARN_SDL_GAME_H
#define LEARN_SDL_GAME_H

#include <SDL.h>

#define FLOAT(x) static_cast<float>(x)

typedef struct
{
  float x;
  float y;
} Vector2;

class Game
{
public:
  Game();

  // Initialize the game
  bool Initialize();

  // Runs the game loop until the game is over
  void RunLoop();

  // Shutdown the game
  void Shutdown();

private:

  // Helper functions for the game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  // Window creates by SDL
  SDL_Window* mWindow;

  // Renderer
  SDL_Renderer* mRenderer;

  // If game should continue run
  bool mIsRunning;

  // Vector2 to represent position for mPaddle and mBall
  Vector2 mPaddlePos;
  Vector2 mBallPos;

  // Vector2 to represent velocity for ball
  Vector2 mBallVel;

  // Ball speed
  float mBallSpeed = 1.0f;

  // Borders for our window
  SDL_Rect mTopWall, mRightWall, mBottomWall;

  // SDL_Rect for our mBall and mPaddle
  SDL_Rect mBall, mPaddle;

  // Paddle direction
  int32_t mPaddleDir = 0;
  float mPaddleSpeed = 300.0f;

  // Keep track of ticks to calculate delta time
  Uint32 mTicksCount = 0;

  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 768;
  const int mThickness = 15;
  const int mPaddleHeight = mThickness * 7;

  // Helper methods
  bool checkYCoordinates() const;
};

#endif //LEARN_SDL_GAME_H
