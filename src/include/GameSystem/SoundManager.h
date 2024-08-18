#pragma once

struct Mix_Chunk;

namespace GameSystem
{

class SoundManager
{
  public:
    SoundManager() = default;
    ~SoundManager();

    static void playSound(Mix_Chunk *sound);
};

} // namespace GameSystem