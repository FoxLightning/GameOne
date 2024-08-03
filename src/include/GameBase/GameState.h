#pragma once
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace GameBase
{

class GameState : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    GameState();

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    std::shared_ptr<GameWorld> gameWorld;
};
}; // namespace GameBase
