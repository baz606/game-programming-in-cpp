//
// Created by baz606 on 6/9/2022.
//

#ifndef LEARN_SDL_GAME_H
#define LEARN_SDL_GAME_H

#include <SDL.h>

struct Vector2
{
  float x;
  float y;
};

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

  // Vector position for mPaddle and mBall
  Vector2 mPaddlePos;
  Vector2 mBallPos;

  // Borders for our window
  SDL_Rect mTopWall, mRightWall, mBottomWall;

  // SDL_Rect for our mBall and mPaddle
  SDL_Rect mBall, mPaddle;

  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 768;
  const int mThickness = 15;
  const int mPaddleHeight = mThickness * 7;
};

#endif //LEARN_SDL_GAME_H
