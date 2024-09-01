#pragma once
#include "GameSystem/Exceptions.h"
#include "SDL3/SDL_scancode.h"
#include <cassert>
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace Game
{
class PlayerController;
}

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

const char *const MainActionName = "MainAction";
const char *const AdvancedActionName = "AdvancedAction";
const char *const MoveLeftName = "MoveLeft";
const char *const MoveRightName = "MoveRight";
const char *const MoveUpName = "MoveUp";
const char *const MoveDownName = "MoveDown";
const char *const EscapeName = "Escape";

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
    static auto GetActionFromName(const std::string &name) -> ActionType;

    std::vector<Mapping> mappingList;
    std::list<Subscription> subscriptionList;
};
}; // namespace GameSystem
