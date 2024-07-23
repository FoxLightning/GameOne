
#include "GameSystem/AppInstance.h"
#include "GameBase/GameState.h"
#include <iostream>
#include <memory>

namespace GameSystem
{

std::shared_ptr<GameBase::GameState> AppInstance::currentAppState;

AppInstance::AppInstance()
{
    currentAppState = std::make_shared<GameBase::GameState>();
}

void AppInstance::Start()
{
    std::cout << "start\n";
}

auto AppInstance::GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>
{
    return currentAppState;
}

} // namespace GameSystem