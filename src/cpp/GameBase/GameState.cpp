#include "GameBase/GameState.h"
#include "Game/PlayerController.h"
#include "GameBase/BaseController.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();

    std::shared_ptr<Game::PlayerController> playerController = std::make_shared<Game::PlayerController>();
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
