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

#include "SDL_image.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

#include <algorithm>

Game::Game()
  :mWindow(nullptr)
  ,mRenderer(nullptr)
  ,mIsRunning(true)
  ,mUpdatingActors(false)
{
}

bool Game::Initialize()
{
  int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  if (sdlResult != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  mWindow = SDL_CreateWindow(
    "Game Programming in C++ (Chapter 2",
    100,
    100,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    0
  );

  if (!mWindow)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!mRenderer)
  {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
  }

  // SDL_Image initialization
  if (IMG_Init(IMG_INIT_PNG) == 0)
  {
    SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
    return false;
  }

  LoadData();

  mTicksCount = SDL_GetTicks();

  return true;
}

void Game::AddActor(Actor *actor)
{
  if (mUpdatingActors)
  {
    mPendingActors.emplace_back(actor);
  }
  else
  {
    mActors.emplace_back(actor);
  }
}

void Game::RemoveActor(Actor *actor)
{
  // check whether it is in pending actors vector
  auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
  if (iter != mPendingActors.end())
  {
    std::iter_swap(iter, mPendingActors.end() - 1);
    mPendingActors.pop_back();
  }

  // check whether it is in actors vector
  iter = std::find(mActors.begin(), mActors.end(), actor);
  if (iter != mActors.end())
  {
    std::iter_swap(iter, mActors.end() - 1);
    mActors.pop_back();
  }
}

bool Game::GetUpdatingActors() const
{
  return mUpdatingActors;
}

void Game::SetUpdatingActors(bool value)
{
  mUpdatingActors = value;
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

void Game::Shutdown()
{
  UnloadData();
  IMG_Quit();
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void Game::ProcessInput()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        mIsRunning = false;
        break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_ESCAPE])
  {
    mIsRunning = false;
  }

  // Process ship input
  mShip->ProcessKeyboard(state);
}

void Game::UpdateGame()
{
  // Compute delta time
  // Wait until 16ms has elapsed since last frame
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
  {
  }

  float deltaTime = FLOAT(SDL_GetTicks() - mTicksCount) / 1000.0f;
  if (deltaTime > 0.05f)
  {
    deltaTime = 0.05f;
  }
  mTicksCount = SDL_GetTicks();

  // Update all actors
  mUpdatingActors = true;
  for (auto actor : mActors)
  {
    actor->Update(deltaTime);
  }
  mUpdatingActors = false;

  // Move any pending actors to mActors
  for (auto pending : mPendingActors)
  {
    mActors.emplace_back(pending);
  }
  mPendingActors.clear();

  // Add any dead actors to a temp vector
  std::vector<Actor*> deadActors;
  for (auto actor : mActors)
  {
    if (actor->GetState() == Actor::EDead)
    {
      deadActors.emplace_back(actor);
    }
  }

  // Delete dead actors (which removes them from mActors)
  for (auto actor : deadActors)
  {
    delete actor;
  }
}

void Game::GenerateOutput()
{
  // Set render draw color
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  // Clear back buffer to the current draw color
  SDL_RenderClear(mRenderer);

  // Draw all sprite components
  for (auto sprite : mSprites)
  {
    sprite->Draw(mRenderer);
  }

  // Swap front buffer with back buffer
  SDL_RenderPresent(mRenderer);
}

SDL_Texture *Game::GetTexture(const std::string &fileName)
{
  SDL_Texture* texture = nullptr;

  // Is the texture already in the map?
  auto iter = mTextures.find(fileName);
  if (iter != mTextures.end())
  {
    texture = iter->second;
  }
  else
  {
    // Load from file
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (!surface)
    {
      SDL_Log("Failed to load texture file %s", SDL_GetError());
      return nullptr;
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
      SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
      return nullptr;
    }
    mTextures.emplace(fileName.c_str(), texture);
  }

  return texture;
}

void Game::LoadData()
{
  // Create player's ship
  mShip = new Ship(this);
  mShip->SetPosition(Vector2(100.0f, 384.0f));
  mShip->SetScale(1.5f);

  // Create Actor for the background
  Actor *temp = new Actor(this);
  temp->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
  // Create the "far back" background
  BGSpriteComponent* bg = new BGSpriteComponent(temp);
  bg->SetScreenSize(Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)));
  std::vector<SDL_Texture*> bgtexs = {
    GetTexture("../src/Assets/Farback01.png"),
    GetTexture("../src/Assets/Farback02.png")
  };
  bg->SetBGTextures(bgtexs);
  bg->SetScrollSpeed(-100.0f);
  // Create the closer background
  bg = new BGSpriteComponent(temp, 50);
  bg->SetScreenSize(Vector2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)));
  bgtexs = {
    GetTexture("../src/Assets/Stars.png"),
    GetTexture("../src/Assets/Stars.png")
  };
  bg->SetBGTextures(bgtexs);
  bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
  // Delete actors
  // Because ~Actor calls RemoveActor so we need to use a different style loop because iter will be re-defined
  while (~mActors.empty())
  {
    delete mActors.back();
  }

  // Destroy textures
  for (auto i : mTextures)
  {
    SDL_DestroyTexture(i.second);
  }
  mTextures.clear();
}

void Game::AddSprite(SpriteComponent *sprite)
{
  // Find the insertion point in the sorted vector
  int myDrawOrder = sprite->GetDrawOrder();
  auto iter = mSprites.begin();
  for ( ; iter != mSprites.end(); iter++)
  {
    if (myDrawOrder < (*iter)->GetDrawOrder())
    {
      break;
    }
  }
  // Inserts element before position of iterator
  mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent *sprite)
{
  auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
  mSprites.erase(iter);
}