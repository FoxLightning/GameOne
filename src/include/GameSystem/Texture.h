#pragma once
#include "Types.h"
#include <memory>
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace GameSystem
{
class Font;

class Texture
{
  public:
    explicit Texture(std::string inPath);
    explicit Texture(const std::shared_ptr<Font> &font, const std::string &text, const LinearColor &color);
    ~Texture();

    [[nodiscard]] auto GetTexture() const -> SDL_Texture *
    {
        return texture;
    };

    [[nodiscard]] auto GetSurface() const -> SDL_Surface *
    {
        return surface;
    };

    [[nodiscard]] auto GetSize() const -> Vector2D;

  private:
    std::string path;
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = nullptr;
};
} // namespace GameSystem