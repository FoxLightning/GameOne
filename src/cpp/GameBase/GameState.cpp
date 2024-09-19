#include "GameBase/GameState.h"
#include "Constants.h"
#include "Game/PlayerShip.h"
#include "GameBase/GameWorld.h"
#include "GameBase/PauseState.h"
#include "GameBase/Scenario.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Collider.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/InputManager.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "UI/HUD.h"
#include <cassert>
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

    GameSystem::EventManager::SubscribeInput(GameSystem::InputActionDelegate{
        .inputContext = GameSystem::InputContext::game,
        .invoker = std::weak_ptr<void>(HUD),
        .callback = [this](GameSystem::EventType eventType, GameSystem::ActionType actionType) {
            OnActionEvent(eventType, actionType);
        }});

    GameSystem::AppInstance::GetInputManager()->SetCurrentInputContext(GameSystem::InputContext::game);
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

void GameState::OnActionEvent(GameSystem::EventType eventType, GameSystem::ActionType actionType)
{
    if (actionType == GameSystem::ActionType::Escape && eventType == GameSystem::EventType::Stop)
    {
        assert(!GameSystem::AppInstance::GetTopState<PauseState>());
        GameSystem::AppInstance::PushState<PauseState>();
    }
}
}; // namespace GameBase
