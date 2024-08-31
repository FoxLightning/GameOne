#pragma once
#include "GameBase/Entity.h"
#include "Types.h"

namespace Game
{
class Explosion final : public GameBase::Entity
{
  public:
    Explosion(Vector2D position, Vector2D direction, double speed, const char *animationName);
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    void CheckCollision(GameSystem::Collider *inCollider) override;
};
} // namespace Game