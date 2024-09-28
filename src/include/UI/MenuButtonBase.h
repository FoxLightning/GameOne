#pragma once
#include "GameSystem/InputManager.h"
#include "UI/CanvasSlot.h"
#include <functional>

namespace GameSystem
{
enum class ActionType : uint8_t;
}

namespace UI
{
class SubMenu;

struct ButtonBinding
{
    GameSystem::ActionType actionType;
    std::string functionName;
};

class MenuButtonBase : public CanvasSlot, public std::enable_shared_from_this<MenuButtonBase>
{
  public:
    virtual void SetHover(bool shouldHover);
    void InitActions(const std::map<GameSystem::ActionType, std::function<void()>> &inActionMap);

    void HandleInput(GameSystem::EventType eventType, GameSystem::ActionType actionType);

  protected:
    virtual void OnStateChange() {};

  private:
    void BindDelegates();
    void UnbindDelegates();
    std::map<GameSystem::ActionType, std::function<void()>> actionMap;
};
} // namespace UI