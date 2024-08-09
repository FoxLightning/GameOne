#include "GameSystem/ResurceManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Renderer.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>

namespace GameSystem
{
ResurceManager::ResurceManager()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        throw CriticalException(std::format("SDL_image could not initialize! IMG_Error: {}", IMG_GetError()));
    }

    for (const char *const texturePath :
         {Const::Textures::ship, Const::Textures::enemy, Const::Textures::missle, Const::Textures::enemyAnimation})
    {
        try
        {
            textureHolder[texturePath] = LoadTexture(texturePath);
        }
        catch (InvalidDataException &exception)
        {
            std::cerr << exception.what() << "\n";
        }
    }
}

auto ResurceManager::GetTexture(const char *const texturePath) -> SDL_Texture *
{
    if (textureHolder.find(texturePath) == textureHolder.end())
    {
        throw InvalidDataException("Texture not loaded.", texturePath);
    }
    return textureHolder[texturePath].texture;
}

auto ResurceManager::LoadTexture(const char *const texturePath) -> TextureData
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(texturePath);
    if (surface == nullptr)
    {
        throw InvalidDataException(std::format("Unable to load image. SDL_Error: {}.", SDL_GetError()), texturePath);
    }
    const std::shared_ptr<Renderer> Renderer = GameSystem::AppInstance::GetRender();
    texture = Renderer->CreateTexture(surface);
    if (texture == nullptr)
    {
        SDL_DestroySurface(surface);
        throw InvalidDataException(std::format("Unable to create texture. SDL_Error: {}.", SDL_GetError()),
                                   texturePath);
    }

    return TextureData{.texture = texture, .surface = surface};
}

ResurceManager::~ResurceManager()
{
    for (const auto &item : textureHolder)
    {
        SDL_DestroySurface(item.second.surface);
    }
}

}; // namespace GameSystem
