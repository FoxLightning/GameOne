#pragma once
#include "GameBase/Entity.h"
#include "Types.h"

namespace Game
{
class SideBorder : public GameBase::Entity
{
  public:
    enum class Side : uint8_t
    {
        left,
        right,
        top
    };

    explicit SideBorder(const Vector2D &worldSize, Side side);

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override {};
    void CheckCollision(Collider *inCollider) override;
};
} // namespace Game