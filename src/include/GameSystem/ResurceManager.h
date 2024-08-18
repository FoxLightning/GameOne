#pragma once
#include <map>

struct SDL_Texture;
struct SDL_Surface;
struct Mix_Chunk;

namespace GameSystem
{
struct TextureData
{
    SDL_Texture *texture;
    SDL_Surface *surface;
};

class ResurceManager final
{
  public:
    ResurceManager();
    ~ResurceManager();

    auto GetTexture(const char *texturePath) -> SDL_Texture *;
    auto GetAudio(const char *audioPath) -> Mix_Chunk *;

  private:
    void LoadTextures();
    void LoadSounds();
    void DestroyTextures();
    void DestroySounds();
    static auto LoadTexture(const char *texturePath) -> TextureData;
    static auto LoadAudio(const char *audioPath) -> Mix_Chunk *;
    std::map<const char *const, TextureData> textureHolder;
    std::map<const char *const, Mix_Chunk *> soundHolder;
};

}; // namespace GameSystem
