#pragma once
#include "Types.h"
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

namespace GameSystem
{
struct RenderAnimation;

class Renderer final
{
  public:
    Renderer();
    virtual ~Renderer();

    void Clear();
    void Render();
    auto CreateTexture(SDL_Surface *surface) -> SDL_Texture *;
    void Draw(const Box2D &shape, SDL_Texture *texture);
    void Draw(const RenderAnimation &inAnimation);
    void Draw(const Box2D &shape, const LinearColor &color);

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

class IRendereble
{
  public:
    virtual ~IRendereble() = default;
    virtual void Draw(std::shared_ptr<Renderer> inRenderer) = 0;
};

}; // namespace GameSystem
