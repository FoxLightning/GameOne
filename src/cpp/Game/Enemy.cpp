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
#include "GameSystem/Exceptions.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <iostream>
#include <memory>

namespace Game
{
Enemy::Enemy(Vector2D position, double speed)
{
    SetPosition(position);
    SetSize(Vector2D(Const::System::Geometry::enemySize, Const::System::Geometry::enemySize));
    SetMaxSpeed(speed);
    SetDirection(Vector2D(0., 1.));
}

void Enemy::Update(double deltaTime)
{
    GameBase::Entity::Update(deltaTime);
}

void Enemy::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    try
    {
        if (auto animation = GetCurrentAnimation())
        {
            inRenderer->Draw(animation->GetRender());
            return;
        }
        auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::Textures::enemy);
        inRenderer->Draw(GetRectangle(), texture);
    }
    catch (GameSystem::InvalidDataException &exception)
    {
        std::cerr << exception.what() << "\n";
        GameBase::Entity::Draw(inRenderer);
    }
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
        auto *texture =
            GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::Textures::enemyExplosionAnimation);
        const std::shared_ptr<GameBase::GameState> &currentGameState = GameSystem::AppInstance::GetCurrentAppState();
        currentGameState->GetGameWorld()->AddEntity<Game::Explosion>(
            GetPosition(), GetDirection(), Vector2D(Const::System::explosionSize, Const::System::explosionSize),
            GetMaxSpeed(), Const::System::explosionAnimationFrameTime, Const::System::enemyExplosionFrames,
            Vector2D(Const::System::explosionSize, Const::System::explosionSize), Vector2L(2, 2), texture);
        SetWaitForDelete();
    }
    else
    {
        auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::Textures::enemyAnimation);
        PlayAnimation(std::make_shared<GameSystem::BaseAnimation>(
            Const::System::animationFrameTime, Const::System::enemyDamageFrames,
            Vector2D(Const::System::Geometry::enemySize, Const::System::Geometry::enemySize), Vector2L(2, 2),
            &GetRectangle(), texture));
    }
}

void Enemy::CheckCollision(PlayerShip * /*inCollider*/)
{
    SetWaitForDelete();
}

} // namespace Game