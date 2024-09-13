#pragma once
#include "Constants.h"
#include "Game/SideBorder.h"
#include "GameBase/Entity.h"

namespace GameSystem
{
class Renderer;
class Image;
} // namespace GameSystem

namespace Game
{
class BottomBorder;
class Enemy;

class PlayerShip final : public GameBase::Entity
{
  public:
    explicit PlayerShip(std::string inConfigName);
    void CheckCollision(GameSystem::Collider *inCollider) override;
    void CheckCollision(Enemy *inCollider) override;
    void CheckCollision(BottomBorder *inCollider) override;
    void CheckCollision(SideBorder *inCollider) override;
    void Update(double deltaTime) override;

    void PullTrigger(bool isPoolingTrigger);

  private:
    static void PlayHitSound();
    void SpawnMissle();
    void BlockMovement(GameSystem::Collider *&inCollider);

    bool triggerPulled = false;
    double timeFromLastShot = 0;
    uint64_t currentIntegrity = Const::Gameplay::maxIntegrity;

    double reloadTime = 0;
    std::string configName;
};

}; // namespace Game