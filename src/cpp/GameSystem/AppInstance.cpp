
#include "GameSystem/AppInstance.h"

#include "GameBase/GameState.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Renderer.h"

#include "SDL3/SDL.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

namespace GameSystem
{

std::shared_ptr<GameBase::GameState> AppInstance::currentAppState;
std::shared_ptr<ConfigManager> AppInstance::configManagerInstance;
std::shared_ptr<Renderer> AppInstance::rendererInstance;

AppInstance::AppInstance()
{
    configManagerInstance = std::make_shared<ConfigManager>();
    rendererInstance = std::make_shared<Renderer>();
    currentAppState = std::make_shared<GameBase::GameState>();
}

void AppInstance::Start()
{
    bool running = true;

    SDL_Event event;

    const auto duration_double = std::chrono::duration<double, std::milli>(1000.);
    const auto frameDelay = std::chrono::duration_cast<std::chrono::milliseconds>(duration_double);
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        auto now = std::chrono::high_resolution_clock::now();
        auto frameTime = now - lastFrameTime;
        if (frameTime >= frameDelay)
        {
            rendererInstance->Clear();
            rendererInstance->Draw();
            rendererInstance->Render();
        }
    }
}

auto AppInstance::GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>
{
    assert(currentAppState);
    return currentAppState;
}

auto AppInstance::GetConfigManager() -> std::shared_ptr<ConfigManager>
{
    assert(configManagerInstance);
    return configManagerInstance;
}

} // namespace GameSystem
