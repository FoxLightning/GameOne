#pragma once

namespace GameSystem
{
class AppInstance
{
  public:
    AppInstance();
    ~AppInstance();

    void Start();

    // static void *GetCurrentAppState();

    // static void *GetRender();
    // static void *GetInputManager();
    // static void *GetResurceManager();

  private:
    // static void *currentAppState;

    // static void *render;
    // static void *inputManager;
    // static void *resurceManager;
};

}; // namespace GameSystem
