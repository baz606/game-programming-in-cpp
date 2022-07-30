//
// Created by baz606 on 7/28/2022.
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

#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game *game)
  :Actor(game)
  ,mRightSpeed(0.0f)
  ,mDownSpeed(0.0f)
{
  // Create an animated sprite component
  AnimSpriteComponent* asc = new AnimSpriteComponent(this);
  std::vector<SDL_Texture*> anims = {
    game->GetTexture("Assets/Ship.01png"),
    game->GetTexture("Assets/Ship.02png"),
    game->GetTexture("Assets/Ship.03png"),
    game->GetTexture("Assets/Ship.04png")
  };
  asc->SetAnimTextures(anims);
}


void Ship::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);

  /**
   * We return a const reference and use it to initialize pos. The value held by the reference is copied to pos.
   * I am assuming this is because we do not directly change the mPosition return by Vector2 from GetPosition() method.
   */
  Vector2 pos = GetPosition();

  // Update position based on speeds and delta time
  pos.x += mRightSpeed * deltaTime;
  pos.y += mDownSpeed * deltaTime;

  // Restrict position to left half of screen
  if (pos.x < 25.0f)
  {
    pos.x = 25.0f;
  }
  else if (pos.x > 500.0f)
  {
    pos.x = 500.0f;
  }
  if (pos.y < 25.0f)
  {
    pos.y = 25.0f;
  }
  else if (pos.y > 743.0f)
  {
    pos.y = 743.0f;
  }
  /**
   * Here we pass pos as a reference to SetPosition() method. The Vector2 pos is passed as reference but the value it
   * holds gets copied over to mPosition Vector2 object.
   */
  SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t *state)
{
  mRightSpeed = 0.0f;
  mDownSpeed = 0.0f;

  // right/left
  if (state[SDL_SCANCODE_D])
  {
    mRightSpeed += 250.0f;
  }
  if (state[SDL_SCANCODE_A])
  {
    mRightSpeed -= 250.0f;
  }
  // up/down
  if (state[SDL_SCANCODE_S])
  {
    mDownSpeed += 300.0f;
  }
  if (state[SDL_SCANCODE_W])
  {
    mDownSpeed -= 300.0f;
  }
}
