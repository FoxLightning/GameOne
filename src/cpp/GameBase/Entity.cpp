#include "GameBase/Entity.h"
#include "Constants.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Collider.h"
#include "GameSystem/Image.h"
#include "GameSystem/PrototypeHolder.h"
#include "Types.h"
#include <cassert>
#include <memory>

namespace GameBase
{

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