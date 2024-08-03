#pragma once
#include <set>

namespace GameSystem
{
enum class ActionType : uint8_t;
}

namespace GameBase
{
class Entity;

class BaseController
{
  public:
    BaseController() = default;
    virtual ~BaseController() = default;

    BaseController(const BaseController &other) = delete;
    auto operator=(const BaseController &other) -> BaseController & = delete;
    BaseController(BaseController &&other) = delete;
    auto operator=(BaseController &&other) -> BaseController & = delete;

    void ApplyCommands(Entity *inEntity);

  protected:
    void AddPendingAction(GameSystem::ActionType InActionType);
    void RemovePendingAction(GameSystem::ActionType InActionType);

  private:
    std::set<GameSystem::ActionType> pendingActions;
};

}; // namespace GameBase