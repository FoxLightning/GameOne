#include "Types.h"
#include <GameBase/Entity.h>
#include <cassert>

namespace GameBase
{
void Collider::CheckCollision(Collider *inCollider)
{
    assert(inCollider);
    if (AreIntersects(rectangle, inCollider->GetRectangle()))
    {
        inCollider->CheckCollision(this);
    }
}

auto Collider::GetRectangle() -> const Box2D &
{
    return rectangle;
}

Entity::Entity(const Box2D &inRectangle, const double &inMaxSpeed)
{
    rectangle = inRectangle;
    maxSpeed = inMaxSpeed;
}

void Entity::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    inRenderer->Draw(rectangle);
}

void Entity::SetWaitForDelete()
{
    waitingForDelete = true;
}

void Entity::Update(const double deltaTime)
{
    rectangle += direction * maxSpeed * powerPercent * deltaTime;
}

auto Entity::IsWaitingForDelete() const -> bool
{
    return waitingForDelete;
}

void Entity::SetDirection(const Vector2D &inSpeed)
{
    direction = Normalize(inSpeed);
}

void Entity::SetEnginePower(const double &inPowerPercent)
{
    powerPercent = inPowerPercent;
}

}; // namespace GameBase