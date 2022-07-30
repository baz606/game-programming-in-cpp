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

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game *game)
  :mState(EActive)
  ,mPosition(Vector2::Zero)
  ,mScale(1.0f)
  ,mRotation(0.0f)
  ,mGame(game)
{
  mGame->AddActor(this);
}

Actor::~Actor()
{
  mGame->RemoveActor(this);

  // Need to delete components
  // Because ~Component calls RemoveComponent, we need a different style loop
  while (!mComponents.empty())
  {
    delete mComponents.back();
  }
}

void Actor::Update(float deltaTime)
{
  if (mState == EActive)
  {
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);
  }
}

void Actor::UpdateComponents(float deltaTime)
{
  for (auto comp : mComponents)
  {
    comp->Update(deltaTime);
  }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component *component)
{
  // Find the insertion point in the sorted vector
  // (The first element with an order higher than me)
  int myOrder = component->GetUpdateOrder();
  auto iter = mComponents.begin();
  for (; iter != mComponents.end(); iter++)
  {
    if (myOrder < (*iter)->GetUpdateOrder())
    {
      break;
    }
  }
  // Inserts the element before position of iterator
  mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component *component)
{
  auto iter = std::find(mComponents.begin(), mComponents.end(), component);
  if (iter != mComponents.end())
  {
    mComponents.erase(iter);
  }
}
