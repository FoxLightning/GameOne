#include "GameSystem/Texture.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Renderer.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
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

Texture::~Texture()
{
    std::cout << std::format("Texture destroyed: \"{}\".\n", path);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}
} // namespace GameSystem