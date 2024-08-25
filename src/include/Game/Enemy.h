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
    explicit Enemy(std::string inConfigName);

    Enemy(const Enemy &other) = default;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void StartIdleAnimation();

    void CheckCollision(GameBase::Collider *inCollider) override;
    void CheckCollision(Bullet *inCollider) override;
    void CheckCollision(PlayerShip *inCollider) override;

  private:
    static void PlayExplosionSound();
    static void PlayHitSound();
    double HP;

    std::string configName;
};
} // namespace Game