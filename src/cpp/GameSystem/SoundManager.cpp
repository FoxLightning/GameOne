#include "GameSystem/SoundManager.h"
#include "SDL3/SDL_init.h"
#include "SDL3_mixer/SDL_mixer.h"

namespace GameSystem
{
void SoundManager::playSound(Mix_Chunk *sound)
{
    if (sound)
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}

SoundManager::~SoundManager()
{
    Mix_Quit();
    SDL_Quit();
}

} // namespace GameSystem