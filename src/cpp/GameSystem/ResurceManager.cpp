#include "GameSystem/ResurceManager.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Constants.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>

namespace GameSystem
{
ResurceManager::ResurceManager()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return;
    }

    for (const auto& texturePath: {Const::ship, Const::enemy, Const::missle})
    {
        textureHolder[texturePath] = LoadTexture(texturePath);
    }
}

auto ResurceManager::GetTexture(const std::string &texturePath) -> SDL_Texture *
{
    if (textureHolder.find(texturePath) == textureHolder.end())
    {
        std::cerr << "Texture: \"" << texturePath << "\" not loaded" << std::endl;
        exit(1);
    }
    return textureHolder[texturePath].texture;
}

auto ResurceManager::LoadTexture(const std::string &texturePath) -> TextureData
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(texturePath.c_str());
    if (surface == nullptr)
    {
        std::cerr << "Unable to load image " << texturePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    texture = GameSystem::AppInstance::GetRender()->CreateTexture(surface);
    if (texture == nullptr)
    {
        std::cerr << "Unable to create texture from " << texturePath << "! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroySurface(surface);
    }

    return TextureData{texture, surface};
}

ResurceManager::~ResurceManager()
{
    for (const auto& item : textureHolder)
    {
        SDL_DestroySurface(item.second.surface);
    }
}

}; // namespace GameSystem
