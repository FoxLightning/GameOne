#include "GameBase/Entity.h"
#include "Constants.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Image.h"
#include "Types.h"
#include <cassert>
#include <exception>
#include <iostream>
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

void Entity::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    try
    {
        image->Draw(inRenderer);
        return;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << "\n";
    }
    inRenderer->Draw(GetRectangle(), Const::Color::Green);
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

void Entity::PlayAnimation(const std::shared_ptr<GameSystem::BaseAnimation> &inAnimation)
{
    animation = inAnimation;
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