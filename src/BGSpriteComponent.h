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

#ifndef LEARD_SDL_CHAPTER_2_BGSPRITECOMPONENT_H
#define LEARD_SDL_CHAPTER_2_BGSPRITECOMPONENT_H

#include "SpriteComponent.h"

class BGSpriteComponent: public SpriteComponent
{
public:
  // Set draw order to default to lower so it is in the background
  BGSpriteComponent(class Actor* owner, int drawOrder = 10);

  // Update/draw overriden from parent
  void Update(float deltaTime) override;
  void Draw(SDL_Renderer* renderer) override;

  // Set the texture used for the background
  void SetBGTextures(const std::vector<SDL_Texture*>& textures);

  // Get/Set screen size and scroll speed
  void SetScreenSize(const Vector2& size) { mScreenSize = size; }

private:
  // Struct to encapsulate each BG image and its offset
  struct BGTexture
  {
    SDL_Texture* mTexture;
    Vector2 mOffset;
  };

  std::vector<BGTexture> mBGTextures;
  Vector2 mScreenSize;
  float mScrollSpeed;
};


#endif //LEARD_SDL_CHAPTER_2_BGSPRITECOMPONENT_H
