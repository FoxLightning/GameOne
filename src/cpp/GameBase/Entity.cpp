#include "GameBase/Entity.h"
#include "Constants.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "Types.h"
#include <cassert>
#include <memory>

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

void Collider::SetRectangle(const Box2D &inRectangle)
{
    rectangle = inRectangle;
}

void Entity::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    auto *texture = GameSystem::AppInstance::GetResurceManager()->GetTexture(Const::ship);
    inRenderer->Draw(GetRectangle(), texture);
}

void Entity::SetWaitForDelete()
{
    waitingForDelete = true;
}

void Entity::Update(const double deltaTime)
{
    if (!controller)
    {
        return; // Add exception
    }
    controller->ApplyCommands(this);
    SetRectangle(GetRectangle() + direction * maxSpeed * powerPercent * deltaTime);
}

auto Entity::IsWaitingForDelete() const -> bool
{
    return waitingForDelete;
}

auto Entity::GetController() -> std::shared_ptr<BaseController>
{
    return controller;
}

void Entity::SetController(const std::shared_ptr<BaseController> &inController)
{
    controller = inController;
}

void Entity::SetDirection(const Vector2D &inSpeed)
{
    direction = Normalize(inSpeed);
}

void Entity::SetEnginePower(const double &inPowerPercent)
{
    powerPercent = inPowerPercent;
}

void Entity::SetMaxSpeed(const double &inMaxSpeed)
{
    maxSpeed = inMaxSpeed;
}

}; // namespace GameBase