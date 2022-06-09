//
// Created by baz606 on 6/9/2022.
//

#ifndef LEARN_SDL_GAME_H
#define LEARN_SDL_GAME_H

#include <SDL.h>

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

  // If game should continue run
  bool mIsRunning;
};

#endif //LEARN_SDL_GAME_H
