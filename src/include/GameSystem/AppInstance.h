#pragma once
#include <memory>
#include <vector>

namespace GameSystem
{
class ConfigManager;
class Renderer;
class InputManager;
class ResurceManager;
class SoundManager;
class PrototypeHolder;
class BaseAppState;

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
    template <typename T, typename... Args>
    static void PushState(Args... args)
    {
        appStatesToPush.push_back(std::dynamic_pointer_cast<BaseAppState>(std::make_shared<T>(args...)));
    }
    template <typename T>
    static auto GetTopState() -> std::shared_ptr<T>
    {
        return std::move(std::dynamic_pointer_cast<T>(appStateStack.back()));
    }
    static void PopState();

    static auto GetCurrentAppState() -> std::shared_ptr<BaseAppState>;

    static auto GetConfigManager() -> std::shared_ptr<ConfigManager>;
    static auto GetInputManager() -> std::shared_ptr<InputManager>;
    static auto GetRender() -> std::shared_ptr<Renderer>;
    static auto GetResurceManager() -> std::shared_ptr<ResurceManager>;
    static auto GetSoundManager() -> std::shared_ptr<SoundManager>;
    static auto GetPrototypeHolder() -> std::shared_ptr<PrototypeHolder>;

  private:
    static std::vector<std::shared_ptr<BaseAppState>> appStateStack;
    static std::vector<std::shared_ptr<BaseAppState>> appStatesToPush;
    static int64_t appStatesToPop;

    static std::shared_ptr<ConfigManager> configManagerInstance;
    static std::shared_ptr<Renderer> rendererInstance;
    static std::shared_ptr<InputManager> inputManagerInstance;
    static std::shared_ptr<ResurceManager> resurceManagerInstance;
    static std::shared_ptr<SoundManager> soundManagerInstance;
    static std::shared_ptr<PrototypeHolder> prototypeHolderInstance;

    static bool isRunning;

    static void UpdateStates(const double &deltaTime);
    static void DrawStates();
    static void AddPendingStates();
    static void RemovePendingStates();
};

}; // namespace GameSystem
