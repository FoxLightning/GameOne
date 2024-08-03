#pragma once
#include "GameBase/Entity.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace Game
{
class PlayerShip final : public GameBase::Entity
{
  public:
    PlayerShip();
    void CheckCollision(Collider *inCollider) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    void Update(double deltaTime) override;

    void PullTrigger(bool isPoolingTrigger);

  private:
    void SpawnMissle();

    bool triggerPulled = false;
    double reloadTime = 0.2;
    double timeFromLastShot = 0;
};

}; // namespace Game