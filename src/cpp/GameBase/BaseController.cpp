#include "GameBase/BaseController.h"
#include "GameSystem/InputManager.h"
#include "GameBase/Entity.h"

namespace GameBase
{

void BaseController::ApplyCommands(Entity* inEntity)
{
    double x = 0;
    double y = 0;
    if (pendingActions.contains(GameSystem::ActionType::MoveDown))
    {
        y += 1;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveUp))
    {
        y -= 1;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveRight))
    {
        x += 1;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveLeft))
    {
        x -= 1;
    }
    inEntity->SetDirection(Vector2D(x, y));
}

void BaseController::AddPendingAction(GameSystem::ActionType inActionType)
{
    pendingActions.emplace(inActionType);
}

void BaseController::RemovePendingAction(GameSystem::ActionType InActionType)
{
    pendingActions.erase(InActionType);
}

}; // namespace GameBase