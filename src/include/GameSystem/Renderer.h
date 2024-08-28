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
struct Texture;

class Renderer final
{
  public:
    Renderer();
    virtual ~Renderer();

    void Clear();
    void Render();
    auto CreateTexture(SDL_Surface *surface) -> SDL_Texture *;
    void Draw(const Box2D &shape, const std::shared_ptr<Texture> &texture);
    void Draw(const Box2D &shape, const Box2D &atlasPos, const std::shared_ptr<Texture> &texture);
    void Draw(const Box2D &shape, const LinearColor &color);
    void SetViewPosition(const Vector2D &inPosition);
    void SetViewScale(const double &inScale);

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    Vector2D viewPosition{0., 0.};
    double viewScale{1.};
};

class IRendereble
{
  public:
    virtual ~IRendereble() = default;
    virtual void Draw(std::shared_ptr<Renderer> inRenderer) = 0;
};

}; // namespace GameSystem
