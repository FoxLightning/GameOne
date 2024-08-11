#pragma once
#include "GameBase/Entity.h"
#include "Types.h"

namespace Game
{
class Explosion final : public GameBase::Entity
{
  public:
    Explosion(Vector2D position, Vector2D direction, double speed, double inFrameTime, int64_t inFrameAmount,
              Vector2D tileSize, Vector2L tiles, SDL_Texture *texture);
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    void CheckCollision(GameBase::Collider *inCollider) override;
};
} // namespace Game