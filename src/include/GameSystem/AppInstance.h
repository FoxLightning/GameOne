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
class ResurceManager;
class SoundManager;

class IUpdateble
{
  public:
    IUpdateble() = default;
    virtual ~IUpdateble() = default;

    virtual void Update(double deltaTime) = 0;
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
    static auto GetRender() -> std::shared_ptr<Renderer>;
    static auto GetResurceManager() -> std::shared_ptr<ResurceManager>;
    static auto GetSoundManager() -> std::shared_ptr<SoundManager>;

  private:
    static std::shared_ptr<GameBase::GameState> currentAppState;

    static std::shared_ptr<ConfigManager> configManagerInstance;
    static std::shared_ptr<Renderer> rendererInstance;
    static std::shared_ptr<InputManager> inputManagerInstance;
    static std::shared_ptr<ResurceManager> resurceManagerInstance;
    static std::shared_ptr<SoundManager> soundManagerInstance;

    static bool isRunning;
};

}; // namespace GameSystem
