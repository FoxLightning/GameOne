#include "Game/PlayerController.h"
#include "Game/PlayerShip.h"
#include "GameBase/BaseController.h"
#include "GameBase/Entity.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/InputManager.h"
#include <array>

namespace Game
{

void PlayerController::SubscribeInput()
{
    const std::array<GameSystem::Subscription, 5> subscriptionArr{
        GameSystem::Subscription{.actionType = GameSystem::ActionType::MainAction,
                                 .owner = weak_from_this(),
                                 .callback = [this](GameSystem::EventType inEventType) -> void {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->AddPendingAction(GameSystem::ActionType::MainAction);
                                     }
                                     else
                                     {
                                         this->RemovePendingAction(GameSystem::ActionType::MainAction);
                                     }
                                 }},
        GameSystem::Subscription{.actionType = GameSystem::ActionType::MoveUp,
                                 .owner = weak_from_this(),
                                 .callback = [this](GameSystem::EventType inEventType) -> void {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->AddPendingAction(GameSystem::ActionType::MoveUp);
                                     }
                                     else
                                     {
                                         this->RemovePendingAction(GameSystem::ActionType::MoveUp);
                                     }
                                 }},
        GameSystem::Subscription{.actionType = GameSystem::ActionType::MoveDown,
                                 .owner = weak_from_this(),
                                 .callback =
                                     [this](GameSystem::EventType inEventType) {
                                         if (inEventType == GameSystem::EventType::Start)
                                         {
                                             this->AddPendingAction(GameSystem::ActionType::MoveDown);
                                         }
                                         else
                                         {
                                             this->RemovePendingAction(GameSystem::ActionType::MoveDown);
                                         }
                                     }},
        GameSystem::Subscription{.actionType = GameSystem::ActionType::MoveLeft,
                                 .owner = weak_from_this(),
                                 .callback =
                                     [this](GameSystem::EventType inEventType) {
                                         if (inEventType == GameSystem::EventType::Start)
                                         {

                                             this->AddPendingAction(GameSystem::ActionType::MoveLeft);
                                         }
                                         else
                                         {
                                             this->RemovePendingAction(GameSystem::ActionType::MoveLeft);
                                         }
                                     }},
        GameSystem::Subscription{.actionType = GameSystem::ActionType::MoveRight,
                                 .owner = weak_from_this(),
                                 .callback = [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->AddPendingAction(GameSystem::ActionType::MoveRight);
                                     }
                                     else
                                     {
                                         this->RemovePendingAction(GameSystem::ActionType::MoveRight);
                                     }
                                 }}};
    for (const auto &subscription : subscriptionArr)
    {
        GameSystem::AppInstance::GetInputManager()->Subscribe(subscription);
    }
}

void PlayerController::ApplyCommands(GameBase::Entity *inEntity)
{
    ApplyMovementCommands(inEntity);
}

void PlayerController::ApplyCommands(PlayerShip *inEntity)
{
    ApplyMovementCommands(inEntity);

    auto pendingActions = GetPendingActions();
    inEntity->PullTrigger(pendingActions.contains(GameSystem::ActionType::MainAction));
}

} // namespace Game
