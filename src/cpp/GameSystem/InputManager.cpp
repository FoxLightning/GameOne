#include "GameSystem/InputManager.h"
#include "GameSystem/AppInstance.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_scancode.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

namespace GameSystem
{

InputManager::InputManager()
{
    // TODO get it from config NOLINT
    mappingList = std::vector<Mapping>{
        {.keycode = SDL_SCANCODE_A, .actionType = ActionType::MoveLeft},
        {.keycode = SDL_SCANCODE_D, .actionType = ActionType::MoveRight},
        {.keycode = SDL_SCANCODE_W, .actionType = ActionType::MoveUp},
        {.keycode = SDL_SCANCODE_S, .actionType = ActionType::MoveDown},
        {.keycode = SDL_SCANCODE_SPACE, .actionType = ActionType::MainAction},
        {.keycode = SDL_SCANCODE_F, .actionType = ActionType::MainAction},
        {.keycode = SDL_SCANCODE_ESCAPE, .actionType = ActionType::Escape},
    };
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

}; // namespace GameSystem
