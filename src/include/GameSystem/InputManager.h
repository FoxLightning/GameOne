#pragma once
#include <list>
#include <vector>
#include <memory>
#include "SDL3/SDL.h"
#include "GameBase/BaseController.h"

namespace GameSystem
{
enum class ActionType : unsigned
{
    MainAction,
    AdvancedAction,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Escape
};

enum class EventType : unsigned
{
    Start,
    Stop,
};

struct Mapping
{
    SDL_Scancode keycode;
    ActionType actionType;
};

struct Subscription
{
    Subscription(const ActionType inActionType, const std::weak_ptr<GameBase::BaseController> &inOwner,
                 const std::function<void(EventType)> &inCallback)
        : actionType(inActionType), owner(inOwner), callback(inCallback)
    {
    }
    ActionType actionType;
    std::weak_ptr<GameBase::BaseController> owner;
    std::function<void(EventType)> callback;
};

class InputManager
{
  public:
    InputManager();
    void Subscribe(const Subscription &inSubscripiton);
    void Unsubscribe(const std::weak_ptr<void> &owner);

    void ProcessInput();

  private:
    void RemoveExpiredSubscribers();

    std::vector<Mapping> mappingList;
    std::list<Subscription> subscriptionList;
};
}; // namespace GameSystem
