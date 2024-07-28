
#include "GameSystem/AppInstance.h"

#include "GameBase/GameState.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/InputManager.h"
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
std::shared_ptr<InputManager> AppInstance::inputManagerInstance;
bool AppInstance::isRunning;

AppInstance::AppInstance()
{
    configManagerInstance = std::make_shared<ConfigManager>();
    rendererInstance = std::make_shared<Renderer>();
    inputManagerInstance = std::make_shared<InputManager>();
}

void AppInstance::Start()
{
    assert(!isRunning);
    isRunning = true;

    const auto duration_double = std::chrono::duration<double, std::milli>(1000. / configManagerInstance->frameRate);
    const auto frameDelay = std::chrono::duration_cast<std::chrono::milliseconds>(duration_double);
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    currentAppState = std::make_shared<GameBase::GameState>();

    while (isRunning)
    {
        inputManagerInstance->ProcessInput();
        auto now = std::chrono::high_resolution_clock::now();
        auto frameTime = now - lastFrameTime;
        if (frameTime >= frameDelay)
        {
            lastFrameTime = now;
            double deltaTime =
                static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(frameTime).count()) / .1E7;
            currentAppState->Update(deltaTime);
        }
        rendererInstance->Clear();
        currentAppState->Draw(rendererInstance);
        rendererInstance->Render();
    }
}

void AppInstance::Stop()
{
    isRunning = false;
}

auto AppInstance::GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>
{
    assert(currentAppState);
    return currentAppState;
}


auto AppInstance::GetInputManager() -> std::shared_ptr<InputManager>
{
    assert(inputManagerInstance);
    return inputManagerInstance;
}

auto AppInstance::GetConfigManager() -> std::shared_ptr<ConfigManager>
{
    assert(configManagerInstance);
    return configManagerInstance;
}

} // namespace GameSystem
