#pragma once
#include "Constants.h"
#include "GameBase/Entity.h"
#include <memory>

namespace GameSystem
{
class Renderer;
class Image;
} // namespace GameSystem

namespace Game
{
class PlayerShip final : public GameBase::Entity
{
  public:
    explicit PlayerShip(std::string inConfigName);
    void CheckCollision(GameBase::Collider *inCollider) override;
    void Update(double deltaTime) override;

    void PullTrigger(bool isPoolingTrigger);

  private:
    void SpawnMissle();

    bool triggerPulled = false;
    double timeFromLastShot = 0;

    double reloadTime = 0;
    std::string configName;
};

}; // namespace Game