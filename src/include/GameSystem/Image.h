#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"

namespace GameSystem
{
class Image : IRendereble
{
  public:
    Image(const char *inPath, Vector2D inPos, Vector2D inSize, Vector2D inPivot);
    void Draw(std::shared_ptr<Renderer> inRenderer) override;

    void SetPos(const Vector2D &inPos);
    [[nodiscard]] auto GetPos() const -> const Vector2D &;

  private:
    const char *path;
    Vector2D pos{0., 0.};
    Vector2D size{0., 0.};
    Vector2D pivot{0.5, 0.5};
};
} // namespace GameSystem
