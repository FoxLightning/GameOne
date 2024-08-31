#include "Game/PlayerShip.h"
#include "Constants.h"
#include "Game/Bullet.h"
#include "Game/PlayerController.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Collider.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/PrototypeHolder.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/SoundManager.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

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
    SetPosition({playerShipAssetTree.get<double>("startPos.x"), playerShipAssetTree.get<double>("startPos.y")});

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

void PlayerShip::CheckCollision(GameSystem::Collider *inCollider)
{
    inCollider->CheckCollision(this);

    double xPenitration = 0.;
    double yPenitration = 0.;
    Vector2D speedToApply = GetSpeedToApply();
    Vector2D CollisionDirection = inCollider->GetPosition() - GetPosition();
    if (CollisionDirection.x() > 0.)
    {
        xPenitration = GetDesiredRectangle().max_corner().x() - inCollider->GetDesiredRectangle().min_corner().x();
    }
    else
    {
        xPenitration = GetDesiredRectangle().min_corner().x() - inCollider->GetDesiredRectangle().max_corner().x();
    }

    if (CollisionDirection.y() > 0.)
    {
        yPenitration = GetDesiredRectangle().max_corner().y() - inCollider->GetDesiredRectangle().min_corner().y();
    }
    else
    {
        yPenitration = GetDesiredRectangle().min_corner().y() - inCollider->GetDesiredRectangle().max_corner().y();
    }

    if ((xPenitration * xPenitration) < (yPenitration * yPenitration))
    {
        speedToApply.x(speedToApply.x() - xPenitration);
    }
    else
    {
        speedToApply.y(speedToApply.y() - yPenitration);
    }
    TryMove(speedToApply);
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
            const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder =
                GameSystem::AppInstance::GetPrototypeHolder();
            const std::shared_ptr<Game::Bullet> bullet =
                prototypeHolder->GetBullet(Const::Prototype::Entity::missleEntity);
            bullet->SetPosition(GetPosition());
            gameWorld->AddEntity(bullet);
        }
    }
}

}; // namespace Game