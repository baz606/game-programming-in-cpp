//
// Created by baz606 on 6/18/2022.
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

#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(Actor *owner, int drawOrder)
  :SpriteComponent(owner, drawOrder)
  ,mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);
  for (auto& bg : mBGTextures)
  {
    // Update the x offset
    bg.mOffset.x += mScrollSpeed * deltaTime;
    // If this is completely off the screen, reset the offset to the right of the last bg texture
    // mScreenSize.z - 1 is because the screen coordinates start at 0,0
    if (bg.mOffset.x < -mScreenSize.x)
    {
      bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
    }
  }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer)
{
  // Draw each background texture
  for (auto& bg : mBGTextures)
  {
    SDL_Rect r;
    // Assume screen size dimensions
    r.w = static_cast<int>(mScreenSize.x);
    r.h = static_cast<int>(mScreenSize.y);
    // Center the rectangle around the position of the owner
    r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
    r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

    // Draw this background
    SDL_RenderCopy(
      renderer,
      bg.mTexture,
      nullptr,
      &r
      );
  }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
  int count = 0;
  for (auto tex : textures)
  {
    BGTexture temp;
    temp.mTexture = tex;

    // Each texture is screen width in offset
    temp.mOffset.x = count * mScreenSize.x;
    temp.mOffset.y = 0;

    mBGTextures.emplace_back(temp);
    count++;
  }
}
