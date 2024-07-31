#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "GameBase/Entity.h"
#include "Types.h"

namespace GameBase
{

class GameWorld : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    GameWorld();
    virtual void Update(const double deltaTime) override;
    virtual void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

template <typename T, typename... Args>
std::weak_ptr<T> AddEntity(Args... args)
    {
        auto entity = std::make_shared<T>(args...);
        entitiesHolder.push_back(entity);
        return std::weak_ptr<T>(entity);
    }

  private:
    void CheckCollisions();
    void UpdateChildren(const double deltaTime);

    std::vector<std::shared_ptr<Entity>> entitiesHolder;
};
}; // namespace GameBase