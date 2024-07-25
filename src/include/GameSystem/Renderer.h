#pragma once

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
    void Draw();

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
}; // namespace GameSystem
