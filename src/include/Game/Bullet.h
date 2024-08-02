#pragma once

#include "GameBase/Entity.h"

namespace Game
{

class Bullet : public GameBase::Entity
{
  public:
    Bullet();
    virtual ~Bullet();
};

}; // namespace Game