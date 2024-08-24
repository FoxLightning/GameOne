#include "Game/Bullet.h"
#include "Constants.h"
#include "Game/Enemy.h"
#include "Game/Explosion.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/PrototypeHolder.h"
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
    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    SetImage(prototypeHolder->GetImage(Const::Prototypes::Image::missle));
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
    const std::shared_ptr<GameBase::GameState> &currentGameState = GameSystem::AppInstance::GetCurrentAppState();
    currentGameState->GetGameWorld()->AddEntity<Game::Explosion>(
        GetPosition(), Vector2D(0., 0.), 0., Const::Prototypes::Animation::missleExplosionAnimation);
    SetWaitForDelete();
}

}; // namespace Game
