#pragma once
#include "UI/Canvas.h"

namespace GameSystem
{
class Image;
}

namespace UI
{
class HUD : public Canvas
{
  public:
    explicit HUD(const Vector2D &screenSize);

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    std::shared_ptr<GameSystem::Image> background;
};
}; // namespace UI