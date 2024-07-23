#pragma once

#include <memory>

namespace GameBase
{
class GameState;
}

namespace GameSystem
{

class AppInstance
{
  public:
    AppInstance();

    static void Start();

    static auto GetCurrentAppState() -> std::shared_ptr<GameBase::GameState>;

    // static void *GetRender();
    // static void *GetInputManager();
    // static void *GetResurceManager();

  private:
    static std::shared_ptr<GameBase::GameState> currentAppState;

    // static void *render;
    // static void *inputManager;
    // static void *resurceManager;
};

}; // namespace GameSystem
