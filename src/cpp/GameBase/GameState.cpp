#include "GameBase/GameState.h"
#include "GameBase/BaseController.h"
#include "GameBase/GameWorld.h"
#include "GameBase/PlayerController.h"
#include "GameSystem/Renderer.h"
#include <iostream>
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();

    std::shared_ptr<PlayerController> playerController = std::make_shared<PlayerController>();
    playerController->SubscribeInput();
    auto entity = gameWorld->AddEntity<Entity>(Box2D(Vector2D(0, 0), Vector2D(50, 50)), 100., playerController);
};

void GameState::Update(const double deltaTime)
{
    gameWorld->Update(deltaTime);
}

void GameState::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    gameWorld->Draw(inRenderer);
}

}; // namespace GameBase
