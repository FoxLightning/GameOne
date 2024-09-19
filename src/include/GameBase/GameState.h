#pragma once
#include "GameSystem/BaseAppState.h"
#include "GameSystem/InputManager.h"
#include <memory>

namespace UI
{
class HUD;
class Menu;
} // namespace UI

namespace GameBase
{
class GameWorld;
class Scenario;

class GameState : public GameSystem::BaseAppState
{
  public:
    GameState();

    auto GetGameWorld() -> std::shared_ptr<GameWorld>;

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void OnActionEvent(GameSystem::EventType eventType, GameSystem::ActionType actionType);

  private:
    std::shared_ptr<GameWorld> gameWorld;
    std::shared_ptr<UI::HUD> HUD;
};
}; // namespace GameBase
