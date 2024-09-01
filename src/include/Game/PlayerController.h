#pragma once
#include "GameBase/BaseController.h"
#include "GameSystem/InputManager.h"
#include <memory>

namespace Game
{
class PlayerShip;

class PlayerController final : public GameBase::BaseController, public std::enable_shared_from_this<PlayerController>
{
  public:
    PlayerController() = default;

    void OnActionEvent(GameSystem::EventType eventType, GameSystem::ActionType actionType);
    void ApplyCommands(PlayerShip *inEntity) override;

    void SubscribeInput();
};

}; // namespace Game
