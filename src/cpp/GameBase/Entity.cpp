#include "GameBase/Entity.h"
#include "Constants.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Image.h"
#include "GameSystem/PrototypeHolder.h"
#include "Types.h"
#include <cassert>
#include <memory>

namespace GameBase
{

auto Collider::GetRectangle() const -> const Box2D &
{
    return rectangle;
}

void Collider::SetSize(Vector2D inSize)
{
    const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();
    const double curPosX = rectangle.min_corner().x() + (curSize.x() * pivot.x());
    const double curPosY = rectangle.min_corner().y() + (curSize.y() * pivot.y());

    const double leftPadding = inSize.x() * pivot.x();
    const double RightPadding = inSize.x() - leftPadding;
    const double topPadding = inSize.y() * pivot.y();
    const double bottomPadding = inSize.y() - topPadding;

    rectangle = Box2D(Vector2D(curPosX - leftPadding, curPosY - topPadding),
                      Vector2D(curPosX + RightPadding, curPosY + bottomPadding));
}

void Collider::SetPosition(Vector2D inPosition)
{
    const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();

    const double leftPadding = curSize.x() * pivot.x();
    const double RightPadding = curSize.x() - leftPadding;
    const double topPadding = curSize.y() * pivot.y();
    const double bottomPadding = curSize.y() - topPadding;

    rectangle = Box2D(Vector2D(inPosition.x() - leftPadding, inPosition.y() - topPadding),
                      Vector2D(inPosition.x() + RightPadding, inPosition.y() + bottomPadding));
}

void Collider::SetPivot(Vector2D inPivot, bool updateRectangle)
{
    pivot = inPivot;
    if (updateRectangle)
    {
        const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();
        const double curPosX = rectangle.min_corner().x() + (curSize.x() * pivot.x());
        const double curPosY = rectangle.min_corner().y() + (curSize.y() * pivot.y());

        const double leftPadding = curSize.x() * pivot.x();
        const double RightPadding = curSize.x() - leftPadding;
        const double topPadding = curSize.y() * pivot.y();
        const double bottomPadding = curSize.y() - topPadding;

        rectangle = Box2D(Vector2D(curPosX - leftPadding, curPosY - topPadding),
                          Vector2D(curPosX + RightPadding, curPosY + bottomPadding));
    }
}

void Collider::Move(Vector2D delta)
{
    rectangle += delta;
}

Entity::Entity(const Entity &other)
    : Collider(other), waitingForDelete(other.waitingForDelete), direction(other.direction), maxSpeed(other.maxSpeed),
      powerPercent(other.powerPercent)
{
    if (other.animation)
    {
        animation = std::make_shared<GameSystem::BaseAnimation>(*other.animation);
    }
    if (other.image)
    {
        image = std::make_shared<GameSystem::Image>(*other.image);
    }
    if (other.controller)
    {
        controller = std::make_shared<BaseController>(*other.controller);
    }
}

void Entity::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    if (image)
    {
        image->Draw(inRenderer);
    }
    else
    {
        inRenderer->Draw(GetRectangle(), Const::Color::Green);
    }
}

void Entity::SetWaitForDelete()
{
    waitingForDelete = true;
}

void Entity::Update(const double deltaTime)
{
    if (animation && animation->IsAnimationFinished())
    {
        animation.reset();
    }
    else if (animation)
    {
        animation->Update(deltaTime);
        animation->SetPosition(GetPosition());
    }

    if (controller)
    {
        controller->ApplyCommands(this);
    }
    Move(direction * maxSpeed * powerPercent * deltaTime);
    if (image)
    {
        image->SetPos(GetPosition());
    }
}

auto Entity::GetPosition() const -> Vector2D
{
    const Box2D &rectangle = GetRectangle();
    return rectangle.min_corner() + (rectangle.max_corner() - rectangle.min_corner()) / 2.;
}

auto Entity::IsWaitingForDelete() const -> bool
{
    return waitingForDelete;
}

auto Entity::GetController() -> std::shared_ptr<BaseController>
{
    return controller;
}

auto Entity::GetCurrentAnimation() const -> const std::shared_ptr<GameSystem::BaseAnimation> &
{
    return animation;
}

auto Entity::GetMaxSpeed() const -> double
{
    return maxSpeed;
}
auto Entity::GetDirection() const -> Vector2D
{
    return direction;
}

void Entity::SetImage(const std::shared_ptr<GameSystem::Image> &inImage)
{
    image = inImage;
}

void Entity::SetController(const std::shared_ptr<BaseController> &inController)
{
    controller = inController;
}

void Entity::PlayAnimation(const char *animatiionName)
{
    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    animation = prototypeHolder->GetAnimation(animatiionName);
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