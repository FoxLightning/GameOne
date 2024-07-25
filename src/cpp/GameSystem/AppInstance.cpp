
#include "GameSystem/AppInstance.h"

#include "GameBase/GameState.h"
#include "GameSystem/ConfigManager.h"

#include <cassert>
#include <iostream>
#include <memory>

namespace GameSystem
{

std::shared_ptr<GameBase::GameState> AppInstance::currentAppState;
std::shared_ptr<ConfigManager> AppInstance::configManagerInstance;

AppInstance::AppInstance()
{
    configManagerInstance = std::make_shared<ConfigManager>();
    currentAppState = std::make_shared<GameBase::GameState>();
}

void AppInstance::Start()
{
    std::cout << "start\n";
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
