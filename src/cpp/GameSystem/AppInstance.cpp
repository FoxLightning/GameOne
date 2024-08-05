
#include "GameSystem/AppInstance.h"
#include "GameBase/GameState.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/InputManager.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include <cassert>
#include <chrono>
#include <memory>
#include <ratio>

namespace GameSystem
{

std::shared_ptr<GameBase::GameState> AppInstance::currentAppState;
std::shared_ptr<ConfigManager> AppInstance::configManagerInstance;
std::shared_ptr<Renderer> AppInstance::rendererInstance;
std::shared_ptr<InputManager> AppInstance::inputManagerInstance;
std::shared_ptr<ResurceManager> AppInstance::resurceManagerInstance;
bool AppInstance::isRunning;

AppInstance::AppInstance()
{
    configManagerInstance = std::make_shared<ConfigManager>();
    rendererInstance = std::make_shared<Renderer>();
    inputManagerInstance = std::make_shared<InputManager>();
    resurceManagerInstance = std::make_shared<ResurceManager>();
}

void AppInstance::Start() // NOLINT
{
    assert(!isRunning);
    isRunning = true;

    const auto duration_double =
        std::chrono::duration<double, std::milli>(1000. / configManagerInstance->GetConfiguration().frameRate);
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
            const double deltaTime =
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

auto AppInstance::GetRender() -> std::shared_ptr<Renderer>
{
    assert(rendererInstance);
    return rendererInstance;
}

auto AppInstance::GetResurceManager() -> std::shared_ptr<ResurceManager>
{
    assert(resurceManagerInstance);
    return resurceManagerInstance;
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
