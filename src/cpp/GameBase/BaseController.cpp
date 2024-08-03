#include "GameBase/BaseController.h"
#include "GameBase/Entity.h"
#include "GameSystem/InputManager.h"
#include <set>

namespace GameBase
{

void BaseController::AddPendingAction(GameSystem::ActionType inActionType)
{
    pendingActions.emplace(inActionType);
}

void BaseController::RemovePendingAction(GameSystem::ActionType InActionType)
{
    pendingActions.erase(InActionType);
}

void BaseController::ApplyMovementCommands(Entity *inEntity)
{
    double x = 0.;
    double y = 0.;
    if (pendingActions.contains(GameSystem::ActionType::MoveDown))
    {
        y += 1.;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveUp))
    {
        y -= 1.;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveRight))
    {
        x += 1.;
    }
    if (pendingActions.contains(GameSystem::ActionType::MoveLeft))
    {
        x -= 1.;
    }
    inEntity->SetDirection(Vector2D(x, y));
}

auto BaseController::GetPendingActions() const -> std::set<GameSystem::ActionType>
{
    return pendingActions;
}

}; // namespace GameBase