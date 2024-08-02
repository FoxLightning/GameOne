#pragma once
#include "GameBase/BaseController.h"

namespace GameBase
{

class PlayerController : public BaseController, public std::enable_shared_from_this<PlayerController>
{
  public:
    PlayerController() = default;

    void SubscribeInput();
};

}; // namespace GameBase
