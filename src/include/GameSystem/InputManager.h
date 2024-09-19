#pragma once
#include "SDL3/SDL_scancode.h"
#include <cassert>
#include <vector>

namespace Game
{
class PlayerController;
}

namespace GameSystem
{
enum class InputContext : uint8_t
{
    none,
    game,
    pause,
};

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
    None,
    Start,
    Stop,
};

struct Mapping
{
    SDL_Scancode keycode;
    ActionType actionType;
};

class InputManager
{
  public:
    InputManager();
    void ProcessInput();
    void SetCurrentInputContext(InputContext inputContext);

  private:
    static auto GetActionFromName(const std::string &name) -> ActionType;

    std::vector<Mapping> mappingList;

    InputContext currentInputContext = InputContext::none;
};
}; // namespace GameSystem
