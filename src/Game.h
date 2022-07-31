//
// Created by baz606 on 6/13/2022.
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

#ifndef LEARD_SDL_CHAPTER_2_GAME_H
#define LEARD_SDL_CHAPTER_2_GAME_H

#include "SDL.h"
#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>

#define FLOAT(x) static_cast<float>(x)

class Game
{
public:
  // Constructor
  Game();

  // Initialize the game
  bool Initialize();

  // Runs the game loop until the game is over
  void RunLoop();

  // Shutdown the game
  void Shutdown();

  SDL_Texture* GetTexture(const std::string &fileName);

  // Actors and pending actors to be updated in the game loop
  // Pending actors are actors that are created during game loop execution
  void AddActor(class Actor* actor);
  void RemoveActor(class Actor* actor);

  void AddSprite(class SpriteComponent* sprite);
  void RemoveSprite(class SpriteComponent* sprite);

  // Getter and Setters
  void SetUpdatingActors(bool value);
  bool GetUpdatingActors() const;

  SDL_Renderer* GetRenderer() const { return mRenderer; }

private:
  // Helper functions for the game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();
  void LoadData();
  void UnloadData();

  // All the actors in the game
  std::vector<class Actor*> mActors;
  // Any pending actors
  std::vector<class Actor*> mPendingActors;

  std::vector<class SpriteComponent*> mSprites;

  // Track if we are updating actors right now
  bool mUpdatingActors;

  // Keep track of ticks
  uint32_t mTicksCount;

  SDL_Window* mWindow;
  SDL_Renderer* mRenderer;

  bool mIsRunning;
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 768;

  // Map of textures loaded
  std::unordered_map<std::string, SDL_Texture*> mTextures;

  // Game-specific
  class Ship* mShip; // Player's ship
};


#endif //LEARD_SDL_CHAPTER_2_GAME_H
