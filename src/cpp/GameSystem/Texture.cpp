#include "GameSystem/Texture.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Font.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace GameSystem
{
Texture::Texture(std::string inPath) : path(std::move(inPath)), surface(IMG_Load(path.c_str()))
{
    if (surface == nullptr)
    {
        throw InvalidDataException(std::format("Unable to load image. SDL_Error: {}", SDL_GetError()), path);
    }
    const std::shared_ptr<Renderer> Renderer = GameSystem::AppInstance::GetRender();
    texture = Renderer->CreateTexture(surface);
    if (texture == nullptr)
    {
        SDL_DestroySurface(surface);
        throw InvalidDataException(std::format("Unable to create texture. SDL_Error: {}.", SDL_GetError()), path);
    }
    std::cout << std::format("Texture created: \"{}\".\n", path);
}

Texture::Texture(const std::shared_ptr<Font> &font, const std::string &text, const LinearColor &color)
    : path(font->GetName() + "(Font)"),
      surface(TTF_RenderText_Blended(font->Get(), text.c_str(), {color.r, color.g, color.b, color.a}))
{
    if (!surface)
    {
        throw InvalidDataException(std::format("Unable to create surface from font. SDL_Error: {}", SDL_GetError()),
                                   path);
    }
    const std::shared_ptr<Renderer> renderer = GameSystem::AppInstance::GetRender();
    texture = renderer->CreateTexture(surface);
    if (!texture)
    {
        SDL_DestroySurface(surface);
        throw InvalidDataException(std::format("Unable to create texture from font. SDL_Error: {}.", SDL_GetError()),
                                   path);
    }
}

auto Texture::GetSize() const -> Vector2D
{
    if (!texture)
    {
        return {0., 0.};
    }
    return {static_cast<double>(surface->w), static_cast<double>(surface->h)};
}

Texture::~Texture()
{
    std::cout << std::format("Texture destroyed: \"{}\".\n", path);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}
} // namespace GameSystem