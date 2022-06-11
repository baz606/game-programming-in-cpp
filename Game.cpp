//
// Created by baz606 on 6/9/2022.
//

#include <iostream>
#include "Game.h"

#define LOG(x) std::cout << x << std::endl

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
  mPaddlePos = { 0, static_cast<float>(SCREEN_HEIGHT / 2) };

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
    // Make sure paddle doesn't move off screen
    if (mPaddlePos.y < (mPaddleHeight/2.0f + mThickness))
    {
      mPaddlePos.y = mPaddleHeight/2.0f + mThickness;
    }
    else if (mPaddlePos.y > (SCREEN_HEIGHT - mPaddleHeight/2.0f - mThickness))
    {
      mPaddlePos.y = SCREEN_HEIGHT - mPaddleHeight/2.0f - mThickness;
    }
  }
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
  SDL_RenderFillRect(mRenderer, &mRightWall);
  SDL_RenderFillRect(mRenderer, &mBottomWall);

  mBall = {
    static_cast<int>(mBallPos.x - mThickness / 2),
    static_cast<int>(mBallPos.y - mThickness / 2),
    mThickness,
    mThickness
  };
  SDL_RenderFillRect(mRenderer, &mBall);

  // The y position may look a bit weird but that is just my attempt of making the mPaddle center with the mBall
  // at the start of the game. I admit this is not the best attempt
  mPaddle = {
    static_cast<int>(mPaddlePos.x),
    static_cast<int>(mPaddlePos.y) - mPaddleHeight + (mThickness * 3),
    mThickness,
    mPaddleHeight
  };
  SDL_RenderFillRect(mRenderer, &mPaddle);
  LOG("x: " << mPaddle.x << "y: " << mPaddle.y);

  // Swap front and back buffer
  SDL_RenderPresent(mRenderer);
}