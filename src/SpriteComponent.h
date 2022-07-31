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

#ifndef LEARD_SDL_CHAPTER_2_SPRITECOMPONENT_H
#define LEARD_SDL_CHAPTER_2_SPRITECOMPONENT_H


#include "Component.h"
#include "Actor.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
  // Lower draw order corresponds with further back or corresponds with the sprite being drawn earlier
  SpriteComponent(Actor *owner, int drawOrder = 100);
  ~SpriteComponent();

  virtual void Draw(SDL_Renderer* renderer);
  virtual void SetTexture(SDL_Texture* texture);

  int GetDrawOrder() const { return mDrawOrder; }
  int GetTextureWidth() const { return mTextureWidth; }
  int GetTextureHeight() const { return mTextureHeight; }

protected:
  // Texture to draw
  SDL_Texture* mTexture;
  // Draw order used for painter's algorithm
  int mDrawOrder;
  // Width/height of texture
  int mTextureWidth;
  int mTextureHeight;
};


#endif //LEARD_SDL_CHAPTER_2_SPRITECOMPONENT_H
