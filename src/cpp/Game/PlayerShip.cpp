#include "Game/PlayerShip.h"
#include "Game/Bullet.h"
#include "Game/PlayerController.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
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

void PlayerShip::Update(double deltaTime)
{
    GameBase::Entity::Update(deltaTime);
    GetController()->ApplyCommands(this);

    timeFromLastShot += deltaTime;

    if (triggerPulled && timeFromLastShot > reloadTime)
    {
        timeFromLastShot = 0;
        triggerPulled = false;

        SpawnMissle();
    }
}

void PlayerShip::PullTrigger(bool isPoolingTrigger)
{
    triggerPulled = isPoolingTrigger;
}

void PlayerShip::SpawnMissle()
{
    if (const std::shared_ptr<GameBase::GameState> currentState = GameSystem::AppInstance::GetCurrentAppState())
    {
        if (const std::shared_ptr<GameBase::GameWorld> gameWorld = currentState->GetGameWorld())
        {
            const Vector2D &position = GetPosition();
            gameWorld->AddEntity<Game::Bullet>(position, Vector2D(0., -1.));
        }
    }
}

}; // namespace Game