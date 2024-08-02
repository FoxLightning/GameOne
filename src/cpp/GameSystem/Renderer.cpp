#include "GameSystem/Renderer.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include "Types.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include <iostream>
#include <memory>

namespace GameSystem
{

Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return;
    }

    const std::shared_ptr<ConfigManager> configManager = AppInstance::GetConfigManager();
    const auto Resolution = configManager->windowResolution;
    window = SDL_CreateWindow("SDL Game Loop Example", Resolution.x(), Resolution.y(), 0);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
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

void Renderer::Draw(const Box2D &shape, SDL_Texture *texture)
{
    const SDL_FRect rectangle = CastSDL_FRect(shape);
    if (texture == nullptr)
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
        SDL_RenderFillRect(renderer, &rectangle);
        return;
    }
    SDL_RenderTexture(renderer, texture, nullptr, &rectangle);
}

auto Renderer::CreateTexture(SDL_Surface *surface) -> SDL_Texture *
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}

void Renderer::Render()
{
    SDL_RenderPresent(renderer);
}

} // namespace GameSystem
