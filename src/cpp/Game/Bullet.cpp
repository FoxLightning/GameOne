#include "Game/Bullet.h"
#include "Constants.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace Game
{

Bullet::Bullet(const Vector2D &start, const Vector2D &direction)
{
    SetSize(Vector2D(40., 40.));
    SetPosition(start);
    SetMaxSpeed(400.);
    SetDirection(direction);
}

void Bullet::Update(double deltaTime)
{
    lifeTime -= deltaTime;
    if (lifeTime < 0)
    {
        SetWaitForDelete();
    }
    GameBase::Entity::Update(deltaTime);
}

void Bullet::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    if (auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::missle))
    {
        inRenderer->Draw(GetRectangle(), texture);
        return;
    }
    GameBase::Entity::Draw(inRenderer);
}

}; // namespace Game
