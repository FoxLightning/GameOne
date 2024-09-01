#include "GameSystem/InputManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keyboard.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

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

void InputManager::Unsubscribe(const std::weak_ptr<void> &owner)
{
    subscriptionList.remove_if([&owner](auto &A) { return A.owner.lock() == owner.lock(); });
}

void InputManager::Subscribe(const Subscription &inSubscripiton)
{
    assert(!inSubscripiton.owner.expired());
    subscriptionList.push_back(inSubscripiton);
}

void InputManager::ProcessInput()
{
    RemoveExpiredSubscribers();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        for (auto mapping : mappingList)
        {
            if (event.key.scancode != mapping.keycode)
            {
                continue;
            }
            EventType eventType = EventType::Stop;
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                eventType = EventType::Start;
            }
            else if (event.type == SDL_EVENT_KEY_UP)
            {
                eventType = EventType::Stop;
            }
            else
            {
                continue;
            }

            for (auto &subscription : subscriptionList)
            {
                if (subscription.actionType != mapping.actionType)
                {
                    continue;
                }
                if (auto _ = subscription.owner.lock())
                {
                    subscription.callback(eventType);
                }
                else
                {
                    std::cerr << "Observer is null!\n";
                }
            }
        }
        if (event.type == SDL_EVENT_QUIT)
        {
            AppInstance::Stop();
        }
    }
}

void InputManager::RemoveExpiredSubscribers()
{
    subscriptionList.remove_if([](auto &A) { return A.owner.expired(); });
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
