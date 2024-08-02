#include "Game/PlayerController.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/InputManager.h"
#include <array>

namespace Game
{

void PlayerController::SubscribeInput()
{
    const std::array<GameSystem::Subscription, 4> subscriptionArr{
        GameSystem::Subscription{GameSystem::ActionType::MoveUp, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
                                     if (inEventType == GameSystem::EventType::Start)
                                     {

                                         this->AddPendingAction(GameSystem::ActionType::MoveUp);
                                     }
                                     else
                                     {
                                         this->RemovePendingAction(GameSystem::ActionType::MoveUp);
                                     }
                                 }},
        GameSystem::Subscription{GameSystem::ActionType::MoveDown, weak_from_this(),
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
        GameSystem::Subscription{GameSystem::ActionType::MoveLeft, weak_from_this(),
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
        GameSystem::Subscription{GameSystem::ActionType::MoveRight, weak_from_this(),
                                 [this](GameSystem::EventType inEventType) {
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

} // namespace Game
