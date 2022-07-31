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

#include "AnimSpriteComponent.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
  :SpriteComponent(owner, drawOrder)
  ,mCurrentFrame(0.0f)
  ,mAnimFPS(0.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);

  // Loop through each mAnimations and update its current frame to draw
  for (auto& anim: mAnimations)
  {
    const int startingIndex = anim.second.startIndex;
    const int endingIndex = anim.second.endIndex;
    const int animationSize = endingIndex - startingIndex + 1;

    // Update the current frame based on frame rate and delta time
    anim.second.currentFrame += anim.second.animFPS * deltaTime;

    // Wrap current frame for now
    // TODO: Add functionality whether to loop over the animation or not
    while (anim.second.currentFrame >= animationSize)
    {
      anim.second.currentFrame -= animationSize;
    }

    // Set the current texture to the Sprite Component parent class
    SetTexture(mAnimTextures[anim.second.currentFrame]);
  }
}

void AnimSpriteComponent::SetAnimation(const std::vector<SDL_Texture *>& textures, const std::string& animationName,
                                       float animFPS, bool isLooping)
{
  AnimInfo animInfo{};

  if (mAnimations.empty() && mAnimTextures.empty())
  {
    mAnimTextures = textures;
    animInfo.startIndex = 0;
    animInfo.currentFrame = animInfo.startIndex;
    animInfo.endIndex = mAnimTextures.size() - 1;  // Last texture's position
    animInfo.isLooping = isLooping;
    animInfo.animFPS = animFPS;

    mAnimations.emplace(animationName.c_str(), animInfo);
    SetTexture(mAnimTextures[animInfo.startIndex]);
  }
  else
  {
    animInfo.startIndex = mAnimTextures.size();  // This is the index of the texture after the last one
    animInfo.currentFrame = animInfo.startIndex;
    animInfo.isLooping = isLooping;
    animInfo.animFPS = animFPS;
    mAnimTextures.insert(mAnimTextures.end(), textures.begin(), textures.end());
    animInfo.endIndex = mAnimTextures.size() - 1;

    mAnimations.emplace(animationName.c_str(), animInfo);
  }
}
