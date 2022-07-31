//
// Created by baz606 on 6/14/2022.
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

#include "SpriteComponent.h"
#include "Actor.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
  :Component(owner)
  ,mTexture(nullptr)
  ,mDrawOrder(drawOrder)
  ,mTextureWidth(0)
  ,mTextureHeight(0)
{
  mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
  mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
  if (mTexture)
  {
    SDL_Rect r;
    // Scale the width/height by owner's scale
    r.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
    r.h = static_cast<int>(mTextureHeight * mOwner->GetScale());
    r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
    r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

    // Draw
    SDL_RenderCopyEx(
        renderer,
        mTexture, // Texture to draw
        nullptr,  // Source rectangle
        &r, // Destination rectangle
        -Math::ToDegrees(mOwner->GetRotation()), // Convert angle
        nullptr,  // Point of rotation
        SDL_FLIP_NONE // Flip behavior
      );
  }
}

void SpriteComponent::SetTexture(SDL_Texture *texture)
{
  mTexture = texture;
  // Get width and height of the texture
  SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}
