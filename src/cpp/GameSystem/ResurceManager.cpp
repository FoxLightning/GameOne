#include "GameSystem/ResurceManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include <cstdlib>
#include <iostream>
#include <memory>

namespace GameSystem
{
ResurceManager::ResurceManager()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << "\n";
        return;
    }

    for (const char *const texturePath : {Const::Textures::ship, Const::Textures::enemy, Const::Textures::missle})
    {
        textureHolder[texturePath] = LoadTexture(texturePath);
    }
}

auto ResurceManager::GetTexture(const char *const texturePath) -> SDL_Texture *
{
    if (textureHolder.find(texturePath) == textureHolder.end())
    {
        std::cerr << "Texture: \"" << texturePath << "\" not loaded" << "\n";
        exit(1);
    }
    return textureHolder[texturePath].texture;
}

auto ResurceManager::LoadTexture(const char *const texturePath) -> TextureData
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(texturePath);
    if (surface == nullptr)
    {
        std::cerr << "Unable to load image " << texturePath << "! SDL_image Error: " << IMG_GetError() << "\n";
    }
    const std::shared_ptr<Renderer> Renderer = GameSystem::AppInstance::GetRender();
    texture = Renderer->CreateTexture(surface);
    if (texture == nullptr)
    {
        std::cerr << "Unable to create texture from " << texturePath << "! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroySurface(surface);
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
