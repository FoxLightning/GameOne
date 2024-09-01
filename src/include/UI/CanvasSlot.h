#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"

namespace UI
{
class CanvasSlot : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    CanvasSlot() = default;
    explicit CanvasSlot(Vector2D inPosition);
    [[nodiscard]] auto GetPosition() const -> const Vector2D &;

  private:
    Vector2D position{0., 0.};
};
} // namespace UI