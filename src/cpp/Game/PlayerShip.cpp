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
#include "GameSystem/PrototypeHolder.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/SoundManager.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <iostream>
#include <memory>

namespace Game
{
PlayerShip::PlayerShip(std::string inConfigName) : configName(std::move(inConfigName))
{
    boost::property_tree::ptree playerShipAssetTree;
    boost::property_tree::read_json(configName, playerShipAssetTree);

    const Vector2D desiredSize = {playerShipAssetTree.get_child("collider").get_child("size").get<double>("x"),
                                  playerShipAssetTree.get_child("collider").get_child("size").get<double>("y")};
    SetSize(desiredSize);
    SetPivot({playerShipAssetTree.get_child("collider").get_child("pivot").get<double>("x"),
              playerShipAssetTree.get_child("collider").get_child("pivot").get<double>("y")});
    SetMaxSpeed(playerShipAssetTree.get<double>("speed"));
    reloadTime = 1. / playerShipAssetTree.get<double>("fireRate");
    auto configManager = GameSystem::AppInstance::GetConfigManager();
    auto resolution = configManager->GetConfiguration().windowResolution;
    SetPosition(
        {static_cast<double>(resolution.x()) / 2., static_cast<double>(resolution.y()) - (desiredSize.y() / 2.)});

    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    SetImage(prototypeHolder->GetImage(playerShipAssetTree.get<std::string>("image")));

    auto playerController = std::make_shared<Game::PlayerController>();
    playerController->SubscribeInput();
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
            std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder =
                GameSystem::AppInstance::GetPrototypeHolder();
            std::shared_ptr<Game::Bullet> bullet = prototypeHolder->GetBullet(Const::Prototype::Entity::missleEntity);
            bullet->SetPosition(GetPosition());
            gameWorld->AddEntity(bullet);
        }
    }
}

}; // namespace Game