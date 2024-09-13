#pragma once
#include "GameBase/Entity.h"

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

    void CheckCollision(GameSystem::Collider *inCollider) override;
    void CheckCollision(Bullet *inCollider) override;
    void CheckCollision(PlayerShip *inCollider) override;

  private:
    static void PlayExplosionSound();
    static void PlayHitSound();

    void Die();
    void Suffer();
    double HP;
    uint64_t reward{1};

    std::string configName;
};
} // namespace Game