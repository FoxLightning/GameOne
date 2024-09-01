#include "GameSystem/Renderer.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Texture.h"
#include "Types.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include <cassert>
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
    const auto resolution = configManager->GetConfiguration().windowResolution;
    const auto defaultResolution = configManager->GetDefaultConfiguration().windowResolution;
    if (static_cast<double>(resolution.x()) / static_cast<double>(resolution.y()) >
        static_cast<double>(defaultResolution.x()) / static_cast<double>(defaultResolution.y()))
    {
        viewScale = static_cast<double>(resolution.y()) / static_cast<double>(defaultResolution.y());
        internalOffset.x(
            (static_cast<double>(resolution.x()) - (static_cast<double>(defaultResolution.x()) * viewScale)) / 2);
    }
    else
    {
        viewScale = static_cast<double>(resolution.x()) / static_cast<double>(defaultResolution.x());
        internalOffset.y(
            (static_cast<double>(resolution.y()) - (static_cast<double>(defaultResolution.y()) * viewScale)) / 2);
    }

    window = SDL_CreateWindow("SDL Game Loop Example", resolution.x(), resolution.y(), 0);
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

void Renderer::SetViewPosition(const Vector2D &inPosition)
{
    offsets.push_back(inPosition * -1.);
}

void Renderer::PopViewPosition()
{
    offsets.pop_back();
}

auto Renderer::GetViewPosition() -> Vector2D
{
    Vector2D offsetSum{0., 0.};
    for (const auto &offset : offsets)
    {
        offsetSum += offset;
    }
    return offsetSum;
}

void Renderer::SetViewScale(const double &inScale)
{
    viewScale = inScale;
}

void Renderer::Draw(const Box2D &shape, const LinearColor &color)
{
    const Vector2D &viewPosition = GetViewPosition();
    const SDL_FRect rectangle = CastSDL_FRect((shape - viewPosition) * viewScale + internalOffset);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Renderer::Draw(const Box2D &shape, const std::shared_ptr<Texture> &texture)
{
    assert(texture && texture->GetTexture());
    const Vector2D &viewPosition = GetViewPosition();
    const SDL_FRect rectangle = CastSDL_FRect((shape - viewPosition) * viewScale + internalOffset);
    SDL_RenderTexture(renderer, texture->GetTexture(), nullptr, &rectangle);
}

void Renderer::Draw(const Box2D &shape, const Box2D &atlasPos, const std::shared_ptr<Texture> &texture)
{
    assert(texture && texture->GetTexture());
    const Vector2D &viewPosition = GetViewPosition();
    const SDL_FRect shapeRectangle = CastSDL_FRect((shape - viewPosition) * viewScale + internalOffset);
    const SDL_FRect atlasPosRectangle = CastSDL_FRect(atlasPos);
    SDL_RenderTexture(renderer, texture->GetTexture(), &atlasPosRectangle, &shapeRectangle);
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
