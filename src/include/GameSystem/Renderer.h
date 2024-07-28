#pragma once
#include "Types.h"
#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace GameSystem
{

class Renderer
{
  public:
    Renderer();
    ~Renderer();

    void Clear();
    void Render();
    void Draw(const Box2D &shape);

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
