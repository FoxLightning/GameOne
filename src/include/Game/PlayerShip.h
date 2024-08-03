#pragma once
#include "GameBase/Entity.h"

namespace Game
{
class PlayerShip final : public GameBase::Entity
{
  public:
    PlayerShip();
    void CheckCollision(Collider *inCollider) override;
};

}; // namespace Game