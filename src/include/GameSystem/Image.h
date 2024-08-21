#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace GameSystem
{
class Texture;

class Image : IRendereble
{
  public:
    Image(std::shared_ptr<Texture> inTexture, Vector2D inPos, Vector2D inSize, Vector2D inPivot);
    explicit Image(const char *assetPath);
    void Draw(std::shared_ptr<Renderer> inRenderer) override;

    void SetPos(const Vector2D &inPos);
    [[nodiscard]] auto GetPos() const -> const Vector2D &;

  private:
    std::shared_ptr<Texture> texture;
    Vector2D pos{0., 0.};
    Vector2D size{0., 0.};
    Vector2D pivot{0.5, 0.5};
};
} // namespace GameSystem
