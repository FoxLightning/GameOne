#include "Game/PlayerShip.h"
#include "Game/PlayerController.h"
#include "GameBase/Entity.h"
#include "Types.h"
#include <memory>

namespace Game
{
PlayerShip::PlayerShip()
    : GameBase::Entity(Box2D(Vector2D(0, 0), Vector2D(50, 50)), 100., std::make_shared<Game::PlayerController>())
{
    if (auto controller = std::dynamic_pointer_cast<PlayerController>(GetController()))
    {
        controller->SubscribeInput();
    }
}

}; // namespace Game