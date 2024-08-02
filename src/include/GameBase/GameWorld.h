#pragma once
#include "Game/PlayerShip.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"

namespace GameBase
{

class GameWorld : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    GameWorld() = default;

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    template <typename T, typename... Args>
    void AddEntity(Args... args)
    {
        entitiesHolder.push_back(std::make_shared<T>(args...));
    }

  private:
    void CheckCollisions();
    void UpdateChildren(const double deltaTime);

    std::vector<std::shared_ptr<Entity>> entitiesHolder;
};
}; // namespace GameBase