#pragma once
#include <map>
#include <memory>

struct SDL_Texture;
struct SDL_Surface;
struct Mix_Chunk;

namespace GameSystem
{
class Texture;

class ResurceManager final
{
  public:
    ResurceManager();

    auto GetTexture(const std::string &path) -> std::weak_ptr<Texture>;
    auto GetAudio(const char *audioPath) -> Mix_Chunk *;

  private:
    void LoadTextures();
    void LoadSounds();
    void DestroySounds();
    static auto LoadAudio(const char *audioPath) -> Mix_Chunk *;
    std::map<std::string, std::shared_ptr<Texture>> textureHolder;
    std::map<const char *const, Mix_Chunk *> soundHolder;
};

}; // namespace GameSystem
