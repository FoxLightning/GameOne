#pragma once
#include "Constants.h"
#include "GameBase/Entity.h"
#include <memory>

namespace GameSystem
{
class Renderer;
}

namespace Game
{
class PlayerShip final : public GameBase::Entity
{
  public:
    PlayerShip();
    void CheckCollision(GameBase::Collider *inCollider) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override;

    void PullTrigger(bool isPoolingTrigger);

  private:
    void SpawnMissle();

    bool triggerPulled = false;
    double reloadTime = Const::Gameplay::playerReloadTime;
    double timeFromLastShot = 0;
};

}; // namespace Game