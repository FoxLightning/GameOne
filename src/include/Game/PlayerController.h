#pragma once
#include "GameBase/BaseController.h"
#include <memory>

namespace Game
{
class PlayerShip;

class PlayerController final : public GameBase::BaseController, public std::enable_shared_from_this<PlayerController>
{
  public:
    PlayerController() = default;

    void ApplyCommands(GameBase::Entity *inEntity) override;
    void ApplyCommands(PlayerShip *inEntity) override;

    void SubscribeInput();
};

}; // namespace Game
