//
// Created by baz606 on 6/17/2022.
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

#ifndef LEARD_SDL_CHAPTER_2_ANIMSPRITECOMPONENT_H
#define LEARD_SDL_CHAPTER_2_ANIMSPRITECOMPONENT_H

#include <unordered_map>
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
  AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

  // Update animation each frame (overriden from component)
  void Update(float deltaTime) override;

  // Set animation given a vector of textures
  void SetAnimation(const std::vector<SDL_Texture*>& textures, const std::string& animationName, float animFPS,
                    bool isLooping);

  // Set/Get the animation FPS
  float GetAnimFPS() const { return mAnimFPS; }
  void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
  // A vector that stores all the textures in animations
  std::vector<SDL_Texture*> mAnimTextures;

  // AnimInfo that stores information about a particular animation. This helps us play the information from the
  // mAnimTextures given the start and end index and its fps.
  struct AnimInfo
  {
    int startIndex;
    int endIndex;
    float currentFrame;
    float animFPS;
    bool isLooping;
  };

  // HashMap to define each animation in terms of its enum name and an index range from mAnimTextures to use
  // in animation
  std::unordered_map<std::string, struct AnimInfo> mAnimations;

  // Current frame displayed
  float mCurrentFrame;
  // Animation frame rate
  float mAnimFPS;
};


#endif //LEARD_SDL_CHAPTER_2_ANIMSPRITECOMPONENT_H
