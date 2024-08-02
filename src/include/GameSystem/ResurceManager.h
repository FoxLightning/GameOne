#pragma once
#include <map>
#include <string>

struct SDL_Texture;
struct SDL_Surface;

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

  private:
    static auto LoadTexture(const char *texturePath) -> TextureData;
    std::map<const char *const, TextureData> textureHolder;
};

}; // namespace GameSystem
