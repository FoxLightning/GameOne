#include "Game/Enemy.h"
#include "Constants.h"
#include "Game/Bullet.h"
#include "Game/Explosion.h"
#include "Game/PlayerShip.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/PrototypeHolder.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/SoundManager.h"
#include "Types.h"
#include <iostream>
#include <memory>

namespace Game
{
Enemy::Enemy(Vector2D position, double speed)
{
    const Vector2D &size = Vector2D(Const::System::Geometry::enemySize, Const::System::Geometry::enemySize);
    SetPosition(position);
    SetSize(size);
    SetMaxSpeed(speed);
    SetDirection(Vector2D(0., 1.));

    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    SetImage(prototypeHolder->GetImage(Const::Prototypes::Image::enemy));
}

void Enemy::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    try
    {
        if (auto animation = GetCurrentAnimation())
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

void Enemy::CheckCollision(GameBase::Collider *inCollider)
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
            GetPosition(), GetDirection(), GetMaxSpeed(), Const::Prototypes::Animation::enemyExplosionAnimation);
        SetWaitForDelete();
        PlayHitSound();
        PlayExplosionSound();
    }
    else
    {
        PlayAnimation(Const::Prototypes::Animation::enemyDamageAnimation);
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