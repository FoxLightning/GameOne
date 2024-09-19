#include "GameBase/PauseState.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/InputManager.h"
#include "GameSystem/Renderer.h"
#include "UI/Menu.h"
#include <cassert>
#include <memory>

namespace GameBase
{

PauseState::PauseState()
{
    GameSystem::AppInstance::GetInputManager()->SetCurrentInputContext(GameSystem::InputContext::pause);
    menu = std::make_shared<UI::Menu>();
    assert(menu);
}

PauseState::~PauseState()
{
    GameSystem::AppInstance::GetInputManager()->SetCurrentInputContext(GameSystem::InputContext::game);
}

void PauseState::Update(double deltaTime)
{
    menu->Update(deltaTime);
}

void PauseState::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    menu->Draw(inRenderer);
}

auto PauseState::IsExclusiveUpdate() -> bool
{
    return true;
}
} // namespace GameBase