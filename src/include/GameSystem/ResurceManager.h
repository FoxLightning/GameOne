#pragma once
#include <map>
#include <memory>

struct SDL_Texture;
struct SDL_Surface;
struct Mix_Chunk;

namespace GameSystem
{
class Texture;
class Font;

class ResurceManager final
{
  public:
    ResurceManager();

    auto GetTexture(const std::string &path) -> std::shared_ptr<Texture>;
    auto GetFont(const std::string &path, int32_t size) -> std::shared_ptr<Font>;
    auto GetAudio(const char *audioPath) -> Mix_Chunk *;

  private:
    void LoadSounds();
    void DestroySounds();
    static auto LoadAudio(const char *audioPath) -> Mix_Chunk *;
    std::map<std::string, std::weak_ptr<Texture>> textureHolder;
    std::map<std::string, std::map<int32_t, std::weak_ptr<Font>>> fontHolder;
    std::map<const char *const, Mix_Chunk *> soundHolder;
};

}; // namespace GameSystem
