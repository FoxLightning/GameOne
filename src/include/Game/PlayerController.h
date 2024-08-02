#pragma once
#include "GameBase/BaseController.h"

namespace Game
{

class PlayerController : public GameBase::BaseController, public std::enable_shared_from_this<PlayerController>
{
  public:
    PlayerController() = default;

    void SubscribeInput();
};

}; // namespace Game
