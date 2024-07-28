#pragma once

#include <memory>

namespace GameBase
{
class GameState;
}

namespace GameSystem
{
class ConfigManager;
class Renderer;
class InputManager;

class IUpdateble
{
  public:
    virtual void Update(const double deltaTime) = 0;
};

class AppInstance
{
  public:
    AppInstance();

    void Start();
    static void Stop();

    static auto GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>;

    static auto GetConfigManager() -> std::shared_ptr<ConfigManager>;
    static auto GetInputManager() -> std::shared_ptr<InputManager>;

private:
    static std::shared_ptr<GameBase::GameState> currentAppState;

    static std::shared_ptr<ConfigManager> configManagerInstance;
    static std::shared_ptr<Renderer> rendererInstance;
    static std::shared_ptr<InputManager> inputManagerInstance;

    static bool isRunning;
};

}; // namespace GameSystem
