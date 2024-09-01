#include "GameBase/GameState.h"
#include "Constants.h"
#include "Game/PlayerShip.h"
#include "GameBase/GameWorld.h"
#include "GameBase/Scenario.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Collider.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "UI/HUD.h"
#include <memory>

namespace GameBase
{

GameState::GameState()
{
    gameWorld = std::make_shared<GameWorld>();
    gameWorld->AddEntity(std::make_shared<Game::PlayerShip>(Const::Prototype::Entity::playerShipEntity));
    const std::shared_ptr<GameSystem::ConfigManager> &configManager = GameSystem::AppInstance::GetConfigManager();
    const Vector2I &defaultResolution = configManager->GetDefaultConfiguration().windowResolution;
    HUD = std::make_shared<UI::HUD>(
        Vector2D{static_cast<double>(defaultResolution.x()), static_cast<double>(defaultResolution.y())});
};

auto GameState::GetGameWorld() -> std::shared_ptr<GameWorld>
{
    return gameWorld;
}

void GameState::Update(const double deltaTime)
{
    gameWorld->Update(deltaTime);
    HUD->Update(deltaTime);
}

void GameState::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    gameWorld->Draw(inRenderer);
    HUD->Draw(inRenderer);
}

}; // namespace GameBase
