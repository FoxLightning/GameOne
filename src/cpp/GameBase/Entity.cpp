#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "Types.h"
#include <GameBase/Entity.h>
#include <cassert>

namespace GameBase
{
void Collider::CheckCollision(Collider *inCollider) // NOLINT recursive is intended here
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

Entity::Entity(const Box2D &inRectangle, const double &inMaxSpeed, const std::shared_ptr<BaseController> &inController)
    : Collider(inRectangle), maxSpeed(inMaxSpeed), waitingForDelete(false), powerPercent(1.), direction(0., 0.),
      controller(inController)
{
}

void Entity::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::ship);
    inRenderer->Draw(rectangle, texture);
}

void Entity::SetWaitForDelete()
{
    waitingForDelete = true;
}

void Entity::Update(const double deltaTime)
{
    controller->ApplyCommands(this);
    rectangle += direction * maxSpeed * powerPercent * deltaTime;
}

auto Entity::IsWaitingForDelete() const -> bool
{
    return waitingForDelete;
}

auto Entity::GetController() -> std::shared_ptr<BaseController>
{
    return controller;
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