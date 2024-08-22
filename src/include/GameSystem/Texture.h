#pragma once
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace GameSystem
{
class Texture
{
  public:
    explicit Texture(std::string inPath);
    ~Texture();

    [[nodiscard]] auto GetTexture() const -> SDL_Texture *
    {
        return texture;
    };

    [[nodiscard]] auto GetSurface() const -> SDL_Surface *
    {
        return surface;
    };

  private:
    std::string path;
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;
};
} // namespace GameSystem