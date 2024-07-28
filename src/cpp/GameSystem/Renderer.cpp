#include "GameSystem/Renderer.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include <SDL3/SDL.h>

namespace GameSystem
{

// TODO add exceptions
Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    const Vector2L Resolution = AppInstance::GetConfigManager()->windowResolution;
    window = SDL_CreateWindow("SDL Game Loop Example", Resolution.x(), Resolution.y(), 0);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Renderer::Draw(const Box2D &shape)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
    SDL_FRect rectangle = CastSDL_FRect(shape);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Renderer::Render()
{
    SDL_RenderPresent(renderer);
}

} // namespace GameSystem
