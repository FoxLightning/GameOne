#include "GameSystem/ResurceManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Renderer.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
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

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateRenderer Error: {}", SDL_GetError()));
    }

    auto AudioSpec = SDL_AudioSpec{.format = SDL_AUDIO_U8, .channels = 2, .freq = 44100}; // NOLINT
    if (Mix_OpenAudio(0, &AudioSpec) < 0)
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateRenderer Error: {}", SDL_GetError()));
    }

    LoadTextures();
    LoadSounds();
}

auto ResurceManager::GetTexture(const char *const texturePath) -> SDL_Texture *
{
    if (textureHolder.find(texturePath) == textureHolder.end())
    {
        throw InvalidDataException("Texture not loaded.", texturePath);
    }
    return textureHolder[texturePath].texture;
}

auto ResurceManager::GetAudio(const char *audioPath) -> Mix_Chunk *
{
    if (!soundHolder.contains(audioPath))
    {
        throw InvalidDataException("Sound not loaded.", audioPath);
    }
    return soundHolder[audioPath];
}

auto ResurceManager::LoadTexture(const char *const texturePath) -> TextureData
{
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(texturePath);
    if (surface == nullptr)
    {
        throw InvalidDataException(std::format("Unable to load image. SDL_Error: {}", SDL_GetError()), texturePath);
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

auto ResurceManager::LoadAudio(const char *const audioPath) -> Mix_Chunk *
{
    Mix_Chunk *sound = Mix_LoadWAV(audioPath);
    if (!sound)
    {
        throw InvalidDataException("Sound not loaded", SDL_GetError());
    }
    return sound;
}

ResurceManager::~ResurceManager()
{
    DestroyTextures();
}

void ResurceManager::LoadTextures()
{
    for (const char *const texturePath :
         {Const::Textures::ship, Const::Textures::enemy, Const::Textures::missle, Const::Textures::enemyAnimation,
          Const::Textures::enemyExplosionAnimation, Const::Textures::bulletExplosionAnimation})
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

void ResurceManager::LoadSounds()
{
    for (const char *const audioPath :
         {Const::Sound::enemyHit, Const::Sound::enemyExplosion, Const::Sound::shipRocketLounch})
    {
        try
        {
            soundHolder[audioPath] = LoadAudio(audioPath);
        }
        catch (InvalidDataException &exception)
        {
            std::cerr << exception.what() << "\n";
        }
    }
}

void ResurceManager::DestroyTextures()
{
    for (const auto &item : textureHolder)
    {
        SDL_DestroySurface(item.second.surface);
    }
}

void ResurceManager::DestroySounds()
{
    for (const auto &item : soundHolder)
    {
        Mix_FreeChunk(item.second);
    }
}

}; // namespace GameSystem
