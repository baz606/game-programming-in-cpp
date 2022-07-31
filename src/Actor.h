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

#ifndef LEARD_SDL_CHAPTER_2_ACTOR_H
#define LEARD_SDL_CHAPTER_2_ACTOR_H

#include <vector>
#include "Game.h"
#include "Math.h"

class Actor
{
public:

  enum State
  {
    EActive, EPaused, EDead
  };

  // Constructor/destructor
  Actor(class Game* game);
  virtual ~Actor();

  // Update function called from Game (not overridable)
  void Update(float deltaTime);

  // Updates all the components attached to the actor (not overridable)
  void UpdateComponents(float deltaTime);

  // Any actor-specific update code (overridable)
  virtual void UpdateActor(float deltaTime);

  // Getters/Setters
  // Position
  void SetPosition(const Vector2& position) { mPosition = position; }
  const Vector2& GetPosition() { return mPosition; }
  // Scale
  void SetScale(float scale) { mScale = scale; }
  float GetScale() const { return mScale; }
  // Rotation
  void SetRotation(float rotation) { mRotation = rotation; }
  float GetRotation() const { return mRotation; }
  // State
  void SetState(State state) { mState = state; }
  State GetState() const { return mState; }
  // Game
  Game* GetGame() const { return mGame; }

  // Add/remove components
  void AddComponent (class Component* component);
  void RemoveComponent (class Component* component);

private:
  // Actor's state
  State mState;

  // Transform
  Vector2 mPosition;    // Center position of actor
  float mScale;         // Uniforms scale of actor (1.0f for 100%)
  float mRotation;      // Rotation angle (in radians)

  // Components held by this actor
  std::vector<class Component*> mComponents;
  Game* mGame;
};


#endif //LEARD_SDL_CHAPTER_2_ACTOR_H
