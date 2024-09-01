#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace UI
{
class HUD;
}

namespace GameBase
{
class GameWorld;
class Scenario;

class GameState : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    GameState();

    auto GetGameWorld() -> std::shared_ptr<GameWorld>;

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    std::shared_ptr<GameWorld> gameWorld;
    std::shared_ptr<UI::HUD> HUD;
};
}; // namespace GameBase
