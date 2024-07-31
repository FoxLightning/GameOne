#pragma once
#include "Types.h"
#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

namespace GameSystem
{

class Renderer
{
  public:
    Renderer();
    ~Renderer();

    void Clear();
    void Render();
    auto CreateTexture(SDL_Surface* surface) -> SDL_Texture *;
    void Draw(const Box2D &shape, SDL_Texture *Texture);

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

class IRendereble
{
  public:
    virtual void Draw(std::shared_ptr<Renderer> inRenderer) = 0;
};

}; // namespace GameSystem
