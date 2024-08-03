#include "GameBase/GameState.h"
#include "Game/Enemy.h"
#include "Game/PlayerShip.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();
    gameWorld->AddEntity<Game::PlayerShip>();
    gameWorld->AddEntity<Game::Enemy>(Vector2D(1280. / 4, 0), 100);
    gameWorld->AddEntity<Game::Enemy>(Vector2D(1280. / 4 * 2, 0), 100);
    gameWorld->AddEntity<Game::Enemy>(Vector2D(1280. / 4 * 3, 0), 100);
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
