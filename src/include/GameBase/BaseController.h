#pragma once
#include "GameSystem/AppInstance.h"
#include <memory>
#include <set>
#include "Types.h"

namespace GameSystem
{
    enum class ActionType : unsigned;
}

namespace GameBase
{
class Entity;

class BaseController : public GameSystem::IUpdateble, public std::enable_shared_from_this<BaseController>
{
  public:
    BaseController(std::weak_ptr<Entity> inEntity);
    virtual void Update(const double deltaTime) override;
    void SubscribeInput();

  private:
    std::weak_ptr<Entity> entity;
    std::set<GameSystem::ActionType> pendingActions;
};

}; // namespace GameBase