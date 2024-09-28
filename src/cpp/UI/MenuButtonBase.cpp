#include "UI/MenuButtonBase.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/InputManager.h"
#include <functional>
#include <map>

namespace UI
{

void MenuButtonBase::SetHover(bool shouldHover)
{
    shouldHover ? BindDelegates() : UnbindDelegates();
}

void MenuButtonBase::BindDelegates()
{
    GameSystem::EventManager::SubscribeInput(
        {.inputContext = GameSystem::InputContext::pause,
         .invoker = weak_from_this(),
         .callback = [this](GameSystem::EventType eventType, GameSystem::ActionType actionType) {
             HandleInput(eventType, actionType);
         }});
}

void MenuButtonBase::HandleInput(GameSystem::EventType eventType, GameSystem::ActionType actionType)
{
    if (eventType == GameSystem::EventType::Start && actionMap[actionType])
    {
        actionMap[actionType]();
    }
}

void MenuButtonBase::UnbindDelegates()
{
    GameSystem::EventManager::UnsubscribeInput(weak_from_this());
}

void MenuButtonBase::InitActions(const std::map<GameSystem::ActionType, std::function<void()>> &inActionMap)
{
    actionMap = inActionMap;
}
} // namespace UI