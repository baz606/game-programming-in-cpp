//
// Created by baz606 on 6/9/2022.
//

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
  mPaddlePos = { 0, static_cast<float>(SCREEN_HEIGHT / 2) };

  // Initialize the mBall and mPaddle SDL_Rect
  mBall = {
    static_cast<int>(mBallPos.x - mThickness / 2),
    static_cast<int>(mBallPos.y - mThickness / 2),
    mThickness,
    mThickness
  };

  // The y position may look a bit weird but that is just my way of making the mPaddle center with the mBall correctly
  // Not the best, I admit
  mPaddle = {
    static_cast<int>(mPaddlePos.x),
    static_cast<int>(mPaddlePos.y) - mPaddleHeight + (mThickness * 3),
    mThickness,
    mPaddleHeight
  };

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
}

void Game::UpdateGame()
{
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
  SDL_RenderFillRect(mRenderer, &mTopWall);
  SDL_RenderFillRect(mRenderer, &mRightWall);
  SDL_RenderFillRect(mRenderer, &mBottomWall);

  SDL_RenderFillRect(mRenderer, &mBall);
  SDL_RenderFillRect(mRenderer, &mPaddle);
  // Swap front and back buffer
  SDL_RenderPresent(mRenderer);
}