#include "Game/Bullet.h"
#include "Constants.h"
#include "Game/Enemy.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <iostream>
#include <memory>

namespace Game
{

Bullet::Bullet(const Vector2D &start, const Vector2D &direction)
{
    SetSize(Vector2D(Const::System::Geometry::bulletSize, Const::System::Geometry::bulletSize));
    SetPosition(start);
    SetMaxSpeed(Const::Gameplay::bulletSpeed);
    SetDirection(direction);
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

void Bullet::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    try
    {
        auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::Textures::missle);
        inRenderer->Draw(GetRectangle(), texture);
    }
    catch (GameSystem::InvalidDataException &exception)
    {
        std::cerr << exception.what() << "\n";
        GameBase::Entity::Draw(inRenderer);
    }
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
    SetWaitForDelete();
}

}; // namespace Game
