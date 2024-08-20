#include "Game/Bullet.h"
#include "Constants.h"
#include "Game/Enemy.h"
#include "Game/Explosion.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "GameSystem/ResurceManager.h"
#include "Types.h"
#include <memory>

namespace Game
{

Bullet::Bullet(const Vector2D &start, const Vector2D &direction)
{
    const Vector2D size{Const::System::Geometry::bulletSize, Const::System::Geometry::bulletSize};
    SetSize(size);
    SetPosition(start);
    SetMaxSpeed(Const::Gameplay::bulletSpeed);
    SetDirection(direction);
    SetImage(std::make_shared<GameSystem::Image>(Const::Textures::missle, start, size, Vector2D(0.5, 0.5)));
}

void Bullet::Update(double deltaTime)
{
    lifeTime -= deltaTime;
    if (lifeTime < 0.)
    {
        SetWaitForDelete();
    }
    GameBase::Entity::Update(deltaTime);
}

auto Bullet::GetDamage() const -> double
{
    return bulletDamage;
}

void Bullet::CheckCollision(GameBase::Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

void Bullet::CheckCollision(Enemy * /*inCollider*/)
{
    const std::shared_ptr<GameSystem::ResurceManager> &resurceManager = GameSystem::AppInstance::GetResurceManager();
    auto *texture = resurceManager->GetTexture(Const::Textures::bulletExplosionAnimation);
    const std::shared_ptr<GameBase::GameState> &currentGameState = GameSystem::AppInstance::GetCurrentAppState();
    currentGameState->GetGameWorld()->AddEntity<Game::Explosion>(
        GetPosition(), Vector2D(0., 0.),
        Vector2D(Const::System::bulletExplosionSize, Const::System::bulletExplosionSize), 0.,
        Const::System::explosionAnimationFrameTime, Const::System::enemyExplosionFrames,
        Vector2D(Const::System::bulletExplosionSize, Const::System::bulletExplosionSize), Vector2L(2, 2), texture);
    SetWaitForDelete();
}

}; // namespace Game
