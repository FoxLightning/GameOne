#include "GameBase/GameState.h"
#include "Constants.h"
#include "Game/PlayerShip.h"
#include "GameBase/GameWorld.h"
#include "GameBase/Scenario.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();
    gameWorld->AddEntity(std::make_shared<Game::PlayerShip>(Const::Prototype::Entity::playerShipEntity));
};

auto GameState::GetGameWorld() -> std::shared_ptr<GameWorld>
{
    return gameWorld;
}

void GameState::Update(const double deltaTime)
{
    gameWorld->Update(deltaTime);
}

void GameState::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    gameWorld->Draw(inRenderer);
}

}; // namespace GameBase
