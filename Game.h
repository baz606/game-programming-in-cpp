//
// Created by baz606 on 6/9/2022.
//

#ifndef LEARN_SDL_GAME_H
#define LEARN_SDL_GAME_H

#include <SDL.h>

#define LOG(x) std::cout << x << std::endl
#define FLOAT(x) static_cast<float>(x)
#define INT(x) static_cast<int32_t>(x)

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

  // Runs the game loop untril the game is over
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
