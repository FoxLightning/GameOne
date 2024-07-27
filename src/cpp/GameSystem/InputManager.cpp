#include "GameSystem/InputManager.h"
#include "GameSystem/AppInstance.h"
#include "SDL3/SDL.h"

namespace GameSystem
{
void InputManager::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            AppInstance::Stop();
        }
    }
}
}; // namespace GameSystem
