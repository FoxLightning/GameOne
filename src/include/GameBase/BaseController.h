#pragma once
#include <set>

namespace Game
{
class PlayerShip;
}

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

    virtual void ApplyCommands(Entity *inEntity) {};
    virtual void ApplyCommands(Game::PlayerShip *inEntity) {};

  protected:
    void AddPendingAction(GameSystem::ActionType InActionType);
    void RemovePendingAction(GameSystem::ActionType InActionType);
    [[nodiscard]] auto GetPendingActions() const -> std::set<GameSystem::ActionType>;

    void ApplyMovementCommands(Entity *inEntity);

  private:
    std::set<GameSystem::ActionType> pendingActions;
};

}; // namespace GameBase