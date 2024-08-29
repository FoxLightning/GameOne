#include "GameBase/GameState.h"
#include "Constants.h"
#include "Game/PlayerShip.h"
#include "GameBase/GameWorld.h"
#include "GameBase/Scenario.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();
    gameWorld->AddEntity(std::make_shared<Game::PlayerShip>(Const::Prototype::Entity::playerShipEntity));
    HUD = std::make_shared<GameSystem::Image>("resurces/textures/HUDBackground.png", Vector2D{1280., 720.},
                                              Vector2D(0., 0.));
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
    HUD->Draw(inRenderer);
}

}; // namespace GameBase
