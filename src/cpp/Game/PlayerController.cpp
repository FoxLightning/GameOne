#include "Game/PlayerController.h"
#include "Game/PlayerShip.h"
#include "GameBase/BaseController.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/InputManager.h"

namespace Game
{

void PlayerController::SubscribeInput()
{
    GameSystem::EventManager::SubscribeInput(GameSystem::InputActionDelegate{
        .inputContext = GameSystem::InputContext::game,
        .invoker = weak_from_this(),
        .callback = [this](GameSystem::EventType eventType, GameSystem::ActionType actionType) {
            OnActionEvent(eventType, actionType);
        }});
}

void PlayerController::OnActionEvent(GameSystem::EventType eventType, GameSystem::ActionType actionType)
{
    switch (eventType)
    {
    case GameSystem::EventType::Start: {
        AddPendingAction(actionType);
        break;
    }
    case GameSystem::EventType::Stop: {
        RemovePendingAction(actionType);
        break;
    }
    default: {
        static_assert(true);
    }
    }
}

void PlayerController::ApplyCommands(PlayerShip *inEntity)
{
    ApplyMovementCommands(inEntity);

    auto pendingActions = GetPendingActions();
    inEntity->PullTrigger(pendingActions.contains(GameSystem::ActionType::MainAction));
}

} // namespace Game
