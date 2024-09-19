#include "GameSystem/InputManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/Exceptions.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_stdinc.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <vector>

namespace
{
auto GetEventTypeFromSDLEvent(const Uint32 SDLEvent) -> GameSystem::EventType
{
    if (SDLEvent == SDL_EVENT_KEY_DOWN)
    {
        return GameSystem::EventType::Start;
    }
    if (SDLEvent == SDL_EVENT_KEY_UP)
    {
        return GameSystem::EventType::Stop;
    }
    return GameSystem::EventType::None;
}
} // namespace

namespace GameSystem
{

InputManager::InputManager()
{
    boost::property_tree::ptree controlsAssetTree;
    boost::property_tree::read_json(Const::AssetPaths::controls, controlsAssetTree);

    for (const auto &binding : controlsAssetTree)
    {
        const auto &actionName = binding.second.get<std::string>("action");
        const auto &action = GetActionFromName(actionName);
        const auto &keyName = binding.second.get<std::string>("key");
        const auto &key = SDL_GetScancodeFromName(keyName.c_str());
        mappingList.push_back({.keycode = key, .actionType = action});
    }
}

void InputManager::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        for (auto mapping : mappingList)
        {
            if (event.key.scancode != mapping.keycode)
            {
                continue;
            }
            if (const EventType eventType = GetEventTypeFromSDLEvent(event.type); eventType != EventType::None)
            {
                EventManager::BroadcastInput(eventType, mapping.actionType, currentInputContext);
            }
        }
        if (event.type == SDL_EVENT_QUIT)
        {
            AppInstance::Stop();
        }
    }
}

void InputManager::SetCurrentInputContext(InputContext inputContext)
{
    currentInputContext = inputContext;
}

auto InputManager::GetActionFromName(const std::string &name) -> ActionType
{
    if (name == MainActionName)
    {
        return ActionType::MainAction;
    }
    if (name == AdvancedActionName)
    {
        return ActionType::AdvancedAction;
    }
    if (name == MoveLeftName)
    {
        return ActionType::MoveLeft;
    }
    if (name == MoveRightName)
    {
        return ActionType::MoveRight;
    }
    if (name == MoveUpName)
    {
        return ActionType::MoveUp;
    }
    if (name == MoveDownName)
    {
        return ActionType::MoveDown;
    }
    if (name == EscapeName)
    {
        return ActionType::Escape;
    }
    throw GameSystem::InvalidControlBinding("Invalid action:", name);
}

}; // namespace GameSystem
