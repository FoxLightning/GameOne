#include "GameSystem/ResurceManager.h"
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/Font.h"
#include "GameSystem/Texture.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_init.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace GameSystem
{

ResurceManager::ResurceManager()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        throw CriticalException(std::format("SDL_image could not initialize! IMG_Error: {}", SDL_GetError()));
    }
    if (!TTF_Init())
    {
        throw CriticalException(std::format("TTF could not initialize! TTF_Error: {}", SDL_GetError()));
    }

    if (!SDL_Init(SDL_INIT_AUDIO))
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateRenderer Error: {}", SDL_GetError()));
    }

    auto AudioSpec = SDL_AudioSpec{.format = SDL_AUDIO_U8, .channels = 2, .freq = 44100}; // NOLINT
    if (!Mix_OpenAudio(0, &AudioSpec))
    {
        throw GameSystem::CriticalException(std::format("SDL_CreateRenderer Error: {}", SDL_GetError()));
    }

    LoadSounds();
}

auto ResurceManager::GetTexture(const std::string &path) -> std::shared_ptr<Texture>
{
    if (auto texture = textureHolder.find(path); texture != textureHolder.end() && !texture->second.expired())
    {
        return texture->second.lock();
    }
    auto textureToAdd = std::make_shared<Texture>(path);
    textureHolder[path] = textureToAdd;
    return textureToAdd;
}

auto ResurceManager::GetFont(const std::string &path, int32_t size) -> std::shared_ptr<Font>
{
    if (auto fontSizeMapItr = fontHolder.find(path); fontSizeMapItr != fontHolder.end())
    {
        if (auto font = fontSizeMapItr->second.find(size);
            font != fontSizeMapItr->second.end() && !font->second.expired())
        {
            return font->second.lock();
        }
        fontSizeMapItr->second[size] = std::make_shared<Font>(path, size);
    }
    std::shared_ptr<Font> font = std::make_shared<Font>(path, size);
    std::map<int32_t, std::weak_ptr<Font>> subMap;
    subMap[size] = std::weak_ptr<Font>(font);
    fontHolder[path] = subMap;
    return font;
}

auto ResurceManager::GetAudio(const char *audioPath) -> Mix_Chunk *
{
    if (!soundHolder.contains(audioPath))
    {
        throw InvalidDataException("Sound not loaded.", audioPath);
    }
    return soundHolder[audioPath];
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

void ResurceManager::LoadSounds()
{
    for (const char *const audioPath :
         {Const::Sound::enemyHit, Const::Sound::enemyExplosion, Const::Sound::shipRocketLounch, Const::Sound::shitHit})
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

void ResurceManager::DestroySounds()
{
    for (const auto &item : soundHolder)
    {
        Mix_FreeChunk(item.second);
    }
}

}; // namespace GameSystem
