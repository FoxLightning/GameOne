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

    auto GetTexture(const std::string &texturePath) -> SDL_Texture *;

  private:
    auto LoadTexture(const std::string &texturePath) -> TextureData;
    std::map<std::string, TextureData> textureHolder;
};

}; // namespace GameSystem
