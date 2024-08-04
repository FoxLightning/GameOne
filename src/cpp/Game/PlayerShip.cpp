#include "Game/PlayerShip.h"
#include "Constants.h"
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
    const Vector2D desiredSize = Vector2D(128., 128);
    const Vector2D startPosition = Vector2D(1280. / 2., 720. - (desiredSize.y() / 2.));
    auto playerController = std::make_shared<Game::PlayerController>();
    playerController->SubscribeInput();
    SetPosition(startPosition);
    SetSize(Vector2D(128., 128));
    SetMaxSpeed(500.);

    if (playerController)
    {
        playerController->SubscribeInput();
        SetController(playerController);
    }
}

void PlayerShip::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    if (auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::ship))
    {
        inRenderer->Draw(GetRectangle(), texture);
        return;
    }
    GameBase::Entity::Draw(inRenderer);
}

void PlayerShip::CheckCollision(GameBase::Collider *inCollider)
{
    inCollider->CheckCollision(this);
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