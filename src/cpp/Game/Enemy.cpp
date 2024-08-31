#include "Game/Enemy.h"
#include "Constants.h"
#include "Game/Bullet.h"
#include "Game/Explosion.h"
#include "Game/PlayerShip.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Collider.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/PrototypeHolder.h"
#include "GameSystem/Renderer.h"
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

Enemy::Enemy(std::string inConfigName) : configName(std::move(inConfigName))
{
    boost::property_tree::ptree enemyAssetTree;
    boost::property_tree::read_json(configName, enemyAssetTree);

    SetSize({enemyAssetTree.get_child("collider").get_child("size").get<double>("x"),
             enemyAssetTree.get_child("collider").get_child("size").get<double>("y")});
    SetPivot({enemyAssetTree.get_child("collider").get_child("pivot").get<double>("x"),
              enemyAssetTree.get_child("collider").get_child("pivot").get<double>("y")});
    SetDirection(Vector2D(0., 1.));
    SetMaxSpeed(enemyAssetTree.get<double>("speed"));
    HP = enemyAssetTree.get<double>("hp");
    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    SetImage(prototypeHolder->GetImage(enemyAssetTree.get<std::string>("image")));
}

void Enemy::StartIdleAnimation()
{
    PlayAnimation(Const::Prototype::Animation::enemyIdleAnimation);
    GetCurrentAnimation()->BindOnAnimationFinished([this]() { StartIdleAnimation(); });
}

void Enemy::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    try
    {
        if (const std::shared_ptr<GameSystem::BaseAnimation> animation = GetCurrentAnimation())
        {
            animation->Draw(inRenderer);
            return;
        }
    }
    catch (GameSystem::InvalidDataException &exception)
    {
        std::cerr << exception.what() << "\n";
    }
    GameBase::Entity::Draw(inRenderer);
}

void Enemy::CheckCollision(GameSystem::Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

void Enemy::CheckCollision(Bullet *inCollider)
{
    HP -= inCollider->GetDamage();

    if (HP <= 0.)
    {
        const std::shared_ptr<GameBase::GameState> &currentGameState = GameSystem::AppInstance::GetCurrentAppState();
        currentGameState->GetGameWorld()->AddEntity<Game::Explosion>(
            GetPosition(), GetDirection(), GetMaxSpeed(), Const::Prototype::Animation::enemyExplosionAnimation);
        SetWaitForDelete();
        PlayHitSound();
        PlayExplosionSound();
    }
    else
    {
        PlayAnimation(Const::Prototype::Animation::enemyDamageAnimation);
        GetCurrentAnimation()->BindOnAnimationFinished([this]() { StartIdleAnimation(); });
        PlayHitSound();
    }
}

void Enemy::PlayExplosionSound()
{
    try
    {
        Mix_Chunk *enemyExplosionSound =
            GameSystem::AppInstance::GetResurceManager()->GetAudio(Const::Sound::enemyExplosion);
        GameSystem::SoundManager::playSound(enemyExplosionSound);
    }
    catch (GameSystem::InvalidDataException &e)
    {
        std::cerr << "Explosion sound is not played\n";
        std::cerr << e.what();
    }
}

void Enemy::PlayHitSound()
{
    try
    {
        Mix_Chunk *enemyExplosionSound = GameSystem::AppInstance::GetResurceManager()->GetAudio(Const::Sound::enemyHit);
        GameSystem::SoundManager::playSound(enemyExplosionSound);
    }
    catch (GameSystem::InvalidDataException &e)
    {
        std::cerr << "Hit sound is not played\n";
        std::cerr << e.what();
    }
}

void Enemy::CheckCollision(PlayerShip * /*inCollider*/)
{
    SetWaitForDelete();
}

} // namespace Game