#pragma once
#include "UI/CanvasSlot.h"
#include <memory>

namespace GameSystem
{
class Renderer;
}

namespace UI
{
class Canvas : CanvasSlot
{
  public:
    explicit Canvas(const Vector2D &inSize);

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void AddChild(const std::shared_ptr<CanvasSlot> &child);
    void DeleteChild(const std::shared_ptr<CanvasSlot> &child);

  private:
    std::vector<std::shared_ptr<CanvasSlot>> children;
    std::vector<std::shared_ptr<CanvasSlot>> childrenToAdd;
    std::vector<std::shared_ptr<CanvasSlot>> childrenToRemove;
};
} // namespace UI