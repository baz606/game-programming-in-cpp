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

#include "Game.h"

Game::Game()
{
  mWindow = nullptr;
  mIsRunning = true;
}

bool Game::Initialize()
{
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);

  if (sdlResult != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  mWindow = SDL_CreateWindow(
    "Game Programming in C++ (Chapter 1)",
    100,                // Top left x-coordinate of window
    100,                // Top left y-coordinate of window
    SCREEN_WIDTH,       // Width of window
    SCREEN_HEIGHT,      // Height of window
    0                 // Flags (0 for no flags set)
    );

  if (!mWindow)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  mRenderer = SDL_CreateRenderer(
    mWindow,    // Window to create renderer for
    -1,           // Let SDL decide with graphics driver to use
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

  if (!mRenderer)
  {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  // Initialize the border SDL_Rect structs
  mTopWall = {0, 0, SCREEN_WIDTH, mThickness};
  mRightWall = {SCREEN_WIDTH - mThickness, 0, mThickness, SCREEN_HEIGHT};
  mBottomWall = {0, SCREEN_HEIGHT - mThickness, SCREEN_WIDTH, mThickness };

  // Initialize the mBall and mPaddle position vectors
  mBallPos = { static_cast<float>(SCREEN_WIDTH / 2), static_cast<float>(SCREEN_HEIGHT / 2) };
  mPaddlePos = { 0, static_cast<float>((SCREEN_HEIGHT / 2) - mPaddleHeight) };

  // Initialize ball velocity vector
  mBallVel = { -200.0f, 235.0f };

  return true;
}

void Game::Shutdown()
{
  SDL_DestroyWindow(mWindow);
  SDL_DestroyRenderer(mRenderer);
  SDL_Quit();
}

void Game::RunLoop()
{
  while (mIsRunning)
  {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::ProcessInput()
{
  SDL_Event event;

  // While there are still events in the queue
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      // Handle different event types
      case SDL_QUIT:
        mIsRunning = false;
        break;
    }
  }

  // Get state of keyboard
  const Uint8* state = SDL_GetKeyboardState(nullptr);
  // Check if escape key is pressed
  if (state[SDL_SCANCODE_ESCAPE])
  {
    mIsRunning = false;
  }

  // Check if keys 'W' or 'S' are pressed and upgrade the paddle's direction accordingly
  mPaddleDir = 0;
  if (state[SDL_SCANCODE_W])
  {
    mPaddleDir -= 1;
  }
  if (state[SDL_SCANCODE_S])
  {
    mPaddleDir += 1;
  }
}

void Game::UpdateGame()
{
  // Wait until 16ms has elapsed since last frame, for target lock frame rate of 60fps
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
  {
  }

  // Delta time is the difference in ticks from last frame
  // (converted to seconds)
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
  // Update tick count for next frame
  mTicksCount = SDL_GetTicks();

  // Clamp maximum delta time value
  if (deltaTime > 0.05f)
  {
    deltaTime = 0.05f;
  }

  // Update objects in game world as function of delta time
  if (mPaddleDir != 0)
  {
    mPaddlePos.y += static_cast<float>(mPaddleDir) * mPaddleSpeed * deltaTime;
    // Make sure paddle doesn't move off the screen
    if (mPaddlePos.y < 0.0f)
    {
      mPaddlePos.y = 0.0f;
    }
    else if (mPaddlePos.y > static_cast<float>(SCREEN_HEIGHT - mPaddleHeight))
    {
      mPaddlePos.y = static_cast<float>(SCREEN_HEIGHT - mPaddleHeight);
    }
  }

  // Collision with the top wall
  if (mBallPos.y <= FLOAT(mThickness) && mBallVel.y < 0.0f)
  {
    mBallVel.y *= -1;
  }
  // Collision with right wall
  if (mBallPos.x >= FLOAT(SCREEN_WIDTH - mThickness) && mBallVel.x > 0.0f)
  {
    mBallVel.x *= -1;
  }
  // Collision with the bottom wall
  if (mBallPos.y >= FLOAT(SCREEN_HEIGHT - mThickness) && mBallVel.y > 0.0f)
  {
    mBallVel.y *= -1;
  }

  // Collision with the paddle
  if (mBallPos.x <= FLOAT(mPaddlePos.x + mThickness * 2) // check whether we are touching the paddle with the ball's x-coordinates
      && mBallPos.x >= 0.0f // check whether ball has not gone past the right wall
      && checkYCoordinates() // check whether we are touching the paddle with the ball's y-coordinates
      && mBallVel.x < 0.0f // check ball's x-velocity is negative to make the collision correct
      )
  {
    mBallVel.x *= -1;
  }

  // Update ball position based on this velocity
  mBallPos.x += mBallVel.x * deltaTime * mBallSpeed;
  mBallPos.y += mBallVel.y * deltaTime * mBallSpeed;
}

void Game::GenerateOutput()
{
  /**
   * Basic Drawing Setup
   */
  SDL_SetRenderDrawColor(
    mRenderer,
    0,
    0,
    255,
    255
    );

  // Clear back buffer to the current draw color
  SDL_RenderClear(mRenderer);

  SDL_SetRenderDrawColor(
    mRenderer,
    255,
    255,
    255,
    255
    );

  //SDL_RenderFillRect(mRenderer, &mTopWall);
  //SDL_RenderFillRect(mRenderer, &mRightWall);
  //SDL_RenderFillRect(mRenderer, &mBottomWall);
  // Update mBall Rect position and graphics

  mBall = {
    static_cast<int>(mBallPos.x - mThickness / 2),
    static_cast<int>(mBallPos.y - mThickness / 2),
    mThickness,
    mThickness
  };
  SDL_RenderFillRect(mRenderer, &mBall);

  // Update mPaddle Rect position and graphics
  mPaddle = {
    static_cast<int>(mPaddlePos.x),
    static_cast<int>(mPaddlePos.y),
    mThickness,
    mPaddleHeight
  };
  SDL_RenderFillRect(mRenderer, &mPaddle);
  //LOG("x: " << mPaddle.x << "y: " << mPaddle.y);

  // Swap front and back buffer
  SDL_RenderPresent(mRenderer);
}

/**
 * Check whether the left top part and left bottom part of the ball's y-coordinates are at least touching the paddle's
 * top right and bottom right y-coordinates
 * @return true if above description is true
 */
bool Game::checkYCoordinates() const
{
   return ((mBallPos.y >= mPaddlePos.y || (mBallPos.y + FLOAT(mThickness)) >= mPaddlePos.y)
      && (mBallPos.y <= (mPaddlePos.y + FLOAT(mPaddleHeight)) || (mBallPos.y + FLOAT(mThickness)) <= (mPaddlePos.y + FLOAT(mPaddleHeight)))
      );
}