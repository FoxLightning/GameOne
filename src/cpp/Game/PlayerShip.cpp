#include "Game/PlayerShip.h"
#include "Constants.h"
#include "Game/Bullet.h"
#include "Game/PlayerController.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Image.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/SoundManager.h"
#include "GameSystem/Texture.h"
#include "Types.h"
#include <iostream>
#include <memory>

namespace Game
{
PlayerShip::PlayerShip()
{
    const Vector2D desiredSize = Vector2D(Const::System::Geometry::playerSize, Const::System::Geometry::playerSize);
    auto configManager = GameSystem::AppInstance::GetConfigManager();
    auto resolution = configManager->GetConfiguration().windowResolution;
    const Vector2D startPosition = Vector2D(static_cast<double>(resolution.x()) / 2.,
                                            static_cast<double>(resolution.y()) - (desiredSize.y() / 2.));
    auto playerController = std::make_shared<Game::PlayerController>();
    playerController->SubscribeInput();
    SetPosition(startPosition);
    SetSize(desiredSize);
    SetMaxSpeed(Const::Gameplay::playerMaxSpeed);

    SetImage(std::make_shared<GameSystem::Image>("resurces/Asset/Image/PlayerShipImage.json"));
    if (playerController)
    {
        playerController->SubscribeInput();
        SetController(playerController);
    }
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

        try
        {
            const std::shared_ptr<GameSystem::ResurceManager> resurceManger =
                GameSystem::AppInstance::GetResurceManager();
            auto *shotShound = resurceManger->GetAudio(Const::Sound::shipRocketLounch);
            GameSystem::SoundManager::playSound(shotShound);
        }
        catch (GameSystem::InvalidDataException &e)
        {
            std::cerr << e.what();
        }
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