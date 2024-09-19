#pragma once

#include "GameSystem/BaseAppState.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace UI
{
class Menu;
}

namespace GameBase
{
class PauseState : public GameSystem::BaseAppState
{
  public:
    PauseState();
    ~PauseState() override;

    auto IsExclusiveUpdate() -> bool override;
    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    std::shared_ptr<UI::Menu> menu;
};
} // namespace GameBase