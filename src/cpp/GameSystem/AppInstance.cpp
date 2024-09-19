
#include "GameSystem/AppInstance.h"
#include "GameBase/GameState.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/InputManager.h"
#include "GameSystem/PrototypeHolder.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/SoundManager.h"
#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include <ranges>
#include <ratio>
#include <vector>

namespace GameSystem
{

std::vector<std::shared_ptr<BaseAppState>> AppInstance::appStateStack;
std::vector<std::shared_ptr<BaseAppState>> AppInstance::appStatesToPush;
int64_t AppInstance::appStatesToPop;
std::shared_ptr<ConfigManager> AppInstance::configManagerInstance;
std::shared_ptr<Renderer> AppInstance::rendererInstance;
std::shared_ptr<InputManager> AppInstance::inputManagerInstance;
std::shared_ptr<ResurceManager> AppInstance::resurceManagerInstance;
std::shared_ptr<SoundManager> AppInstance::soundManagerInstance;
std::shared_ptr<PrototypeHolder> AppInstance::prototypeHolderInstance;
bool AppInstance::isRunning;

AppInstance::AppInstance()
{
    configManagerInstance = std::make_shared<ConfigManager>();
    rendererInstance = std::make_shared<Renderer>();
    inputManagerInstance = std::make_shared<InputManager>();
    resurceManagerInstance = std::make_shared<ResurceManager>();
    soundManagerInstance = std::make_shared<SoundManager>();
    prototypeHolderInstance = std::make_shared<PrototypeHolder>();
}

void AppInstance::UpdateStates(const double &deltaTime)
{
    for (auto &state : std::views::reverse(appStateStack))
    {
        state->Update(deltaTime);
        if (state->IsExclusiveUpdate())
        {
            break;
        }
    }
}

void AppInstance::DrawStates()
{
    rendererInstance->Clear();
    for (auto &state : appStateStack)
    {
        state->Draw(rendererInstance);
        if (state->IsExclusiveDraw())
        {
            break;
        }
    }
    rendererInstance->Render();
}

void AppInstance::AddPendingStates()
{
    appStateStack.append_range(appStatesToPush);
    appStatesToPush.clear();
}

void AppInstance::RemovePendingStates()
{
    assert(appStateStack.size() > appStatesToPop);
    appStateStack.erase(appStateStack.end() - appStatesToPop, appStateStack.end());
    appStatesToPop = 0;
}

void AppInstance::Start() // NOLINT
{
    assert(!isRunning);
    isRunning = true;

    const auto duration_double =
        std::chrono::duration<double, std::milli>(1000. / configManagerInstance->GetConfiguration().frameRate);
    const auto frameDelay = std::chrono::duration_cast<std::chrono::milliseconds>(duration_double);
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    appStateStack.emplace_back(std::dynamic_pointer_cast<BaseAppState>(std::make_shared<GameBase::GameState>()));

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
            UpdateStates(deltaTime);
        }
        DrawStates();

        AddPendingStates();
        RemovePendingStates();
    }
}

void AppInstance::Stop()
{
    isRunning = false;
}

void AppInstance::PopState()
{
    appStatesToPop++;
}

auto AppInstance::GetCurrentAppState() -> std::shared_ptr<BaseAppState>
{
    assert(!appStateStack.empty());
    return appStateStack.back();
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

auto AppInstance::GetSoundManager() -> std::shared_ptr<SoundManager>
{
    assert(configManagerInstance);
    return soundManagerInstance;
}

auto AppInstance::GetPrototypeHolder() -> std::shared_ptr<PrototypeHolder>
{
    assert(prototypeHolderInstance);
    return prototypeHolderInstance;
}

} // namespace GameSystem
