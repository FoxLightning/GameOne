#pragma once
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"

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
        entitiesToAdd.push_back(std::make_shared<T>(args...));
    }

  private:
    void CheckCollisions();
    void UpdateChildren(double deltaTime);
    void RemoveStaleObjects();
    void AddPendingObjects();

    std::vector<std::shared_ptr<Entity>> entitiesHolder;
    std::vector<std::shared_ptr<Entity>> entitiesToAdd;
};
}; // namespace GameBase