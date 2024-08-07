#include "GameSystem/Renderer.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Exceptions.h"
#include "Types.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include <format>
#include <memory>

namespace GameSystem
{

Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw GameSystem::CriticalException(std::format("SDL_Init Error: {}", SDL_GetError()));
    }

    const std::shared_ptr<ConfigManager> configManager = AppInstance::GetConfigManager();
    const auto Resolution = configManager->GetConfiguration().windowResolution;
    window = SDL_CreateWindow("SDL Game Loop Example", Resolution.x(), Resolution.y(), 0);
    if (window == nullptr)
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateWindow Error: {}", SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr)
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateRenderer Error: {}", SDL_GetError()));
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
    SDL_SetRenderDrawColor(renderer, Const::Color::Black.r, Const::Color::Black.g, Const::Color::Black.b,
                           Const::Color::Black.a);
    SDL_RenderClear(renderer);
}

void Renderer::Draw(const Box2D &shape, const LinearColor &color)
{
    const SDL_FRect rectangle = CastSDL_FRect(shape);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Renderer::Draw(const Box2D &shape, SDL_Texture *texture)
{
    const SDL_FRect rectangle = CastSDL_FRect(shape);
    if (texture == nullptr)
    {
        SDL_SetRenderDrawColor(renderer, Const::Color::Red.r, Const::Color::Red.g, Const::Color::Red.b,
                               Const::Color::Red.a);
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
