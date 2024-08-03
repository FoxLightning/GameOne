#include "Game/PlayerShip.h"
#include "Game/PlayerController.h"
#include "Types.h"
#include <memory>

namespace Game
{
PlayerShip::PlayerShip()
{
    auto playerController = std::make_shared<Game::PlayerController>();
    playerController->SubscribeInput();
    SetRectangle(Box2D(Vector2D(0., 0.), Vector2D(100., 100.)));
    SetEnginePower(1.);
    SetMaxSpeed(200.);

    if (playerController)
    {
        playerController->SubscribeInput();
        SetController(playerController);
    }
}

void PlayerShip::CheckCollision(Collider *inCollider)
{
}

}; // namespace Game