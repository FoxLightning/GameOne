#pragma once
#include "Game/PlayerController.h"
#include "SDL3/SDL_scancode.h"
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace GameSystem
{
enum class ActionType : uint8_t
{
    MainAction,
    AdvancedAction,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Escape
};

enum class EventType : uint8_t
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
    ActionType actionType;
    std::weak_ptr<Game::PlayerController> owner;
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
