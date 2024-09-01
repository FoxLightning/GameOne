#pragma once
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

class PlayerShip final : public GameBase::Entity
{
  public:
    explicit PlayerShip(std::string inConfigName);
    void CheckCollision(GameSystem::Collider *inCollider) override;
    void CheckCollision(BottomBorder *inCollider) override;
    void CheckCollision(SideBorder *inCollider) override;
    void Update(double deltaTime) override;

    void PullTrigger(bool isPoolingTrigger);

  private:
    void SpawnMissle();
    void BlockMovement(GameSystem::Collider *&inCollider);

    bool triggerPulled = false;
    double timeFromLastShot = 0;

    double reloadTime = 0;
    std::string configName;
};

}; // namespace Game