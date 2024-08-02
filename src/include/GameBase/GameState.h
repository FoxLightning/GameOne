#pragma once
#include "GameBase/BaseController.h"
#include "GameBase/Entity.h"
#include "GameBase/GameWorld.h"
#include "Types.h"
#include <memory>
#include <vector>

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
