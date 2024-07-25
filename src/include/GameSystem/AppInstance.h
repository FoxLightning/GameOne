#pragma once

#include <memory>

namespace GameBase
{
class GameState;
}

namespace GameSystem
{
class ConfigManager;

class AppInstance
{
  public:
    AppInstance();

    static void Start();

    static auto GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>;

    static auto GetConfigManager() -> std::shared_ptr<ConfigManager>;
    // static void *GetRender();
    // static void *GetInputManager();
    // static void *GetResurceManager();

  private:
    static std::shared_ptr<GameBase::GameState> currentAppState;

    static std::shared_ptr<ConfigManager> configManagerInstance;
    // static void *render;
    // static void *inputManager;
    // static void *resurceManager;
};

}; // namespace GameSystem
