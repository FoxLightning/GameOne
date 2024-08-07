#include "Game/Enemy.h"
#include "Constants.h"
#include "Game/PlayerShip.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
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

void Enemy::CheckCollision(Bullet * /*inCollider*/)
{
    SetWaitForDelete();
}

void Enemy::CheckCollision(PlayerShip * /*inCollider*/)
{
    SetWaitForDelete();
}

} // namespace Game