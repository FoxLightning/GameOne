#include "GameBase/BaseController.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/InputManager.h"
#include <array>
#include <memory>

namespace GameBase
{

BaseController::BaseController(std::weak_ptr<Entity> inEntity)
{
    entity = inEntity;
    if (auto entityShared = entity.lock())
    {
        entityShared->SetEnginePower(1.f);
    }
}

void BaseController::SubscribeInput()
{

    std::array<GameSystem::Subscription, 4> subscriptionArr{
        GameSystem::Subscription{GameSystem::ActionType::MoveUp, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->pendingActions.insert(GameSystem::ActionType::MoveUp);
                                     }
                                     else
                                     {
                                         this->pendingActions.erase(GameSystem::ActionType::MoveUp);
                                     }
                                 }},
        GameSystem::Subscription{GameSystem::ActionType::MoveDown, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->pendingActions.insert(GameSystem::ActionType::MoveDown);
                                     }
                                     else
                                     {
                                         this->pendingActions.erase(GameSystem::ActionType::MoveDown);
                                     }
                                 }},
        GameSystem::Subscription{GameSystem::ActionType::MoveLeft, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->pendingActions.insert(GameSystem::ActionType::MoveLeft);
                                     }
                                     else
                                     {
                                         this->pendingActions.erase(GameSystem::ActionType::MoveLeft);
                                     }
                                 }},
        GameSystem::Subscription{GameSystem::ActionType::MoveRight, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->pendingActions.insert(GameSystem::ActionType::MoveRight);
                                     }
                                     else
                                     {
                                         this->pendingActions.erase(GameSystem::ActionType::MoveRight);
                                     }
                                 }}};
    for (auto subscription : subscriptionArr)
    {
        GameSystem::AppInstance::GetInputManager()->Subscribe(subscription);
    }
}

void BaseController::Update(const double deltaTime)
{
    if (auto entityShared = entity.lock())
    {
        Vector2D directionRight{pendingActions.count(GameSystem::ActionType::MoveRight) ? 1. : 0., 0.};
        Vector2D directionLeft{pendingActions.count(GameSystem::ActionType::MoveLeft) ? -1. : 0., 0.};
        Vector2D directionUp{0., pendingActions.count(GameSystem::ActionType::MoveDown) ? 1. : 0.};
        Vector2D directionDown{0., pendingActions.count(GameSystem::ActionType::MoveUp) ? -1. : 0.};
        entityShared->SetDirection(Normalize(directionRight + directionLeft + directionUp + directionDown));
    }
}

}; // namespace GameBase