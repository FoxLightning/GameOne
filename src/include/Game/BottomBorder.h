#pragma once
#include "GameBase/Entity.h"
#include "Types.h"

namespace Game
{
class BottomBorder : public GameBase::Entity
{
  public:
    explicit BottomBorder(const Vector2D &worldSize);

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override {};
    void CheckCollision(Collider *inCollider) override;
    void CheckCollision(Game::Enemy *inCollider) override;
};
} // namespace Game