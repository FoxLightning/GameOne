#pragma once
#include "Constants.h"
#include "GameBase/Entity.h"
#include "Types.h"

namespace Game
{
class PlayerShip;
class Bullet;

class Enemy final : public GameBase::Entity
{
  public:
    Enemy(Vector2D position, double speed);
    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    void CheckCollision(GameBase::Collider *inCollider) override;
    void CheckCollision(Bullet *inCollider) override;
    void CheckCollision(PlayerShip *inCollider) override;

  private:
    double HP = Const::Gameplay::enemyHP;
};
} // namespace Game