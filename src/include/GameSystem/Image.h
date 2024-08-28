#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>
#include <string>

namespace GameSystem
{
class Texture;

class Image : IRendereble
{
  public:
    Image(const std::string &inTexturePath, const Vector2D &inSize, const Vector2D &inPivot);
    explicit Image(std::string name);
    Image(const Image &other) = default;

    auto operator=(const Image &other) -> Image & = delete;

    void Draw(std::shared_ptr<Renderer> inRenderer) override;
    void SetPos(const Vector2D &inPos);
    [[nodiscard]] auto GetSize() const -> const Vector2D &;
    [[nodiscard]] auto GetPos() const -> const Vector2D &;

  private:
    std::shared_ptr<Texture> texture;
    Vector2D pos{0., 0.};
    Vector2D size{0., 0.};
    Vector2D pivot{0.5, 0.5};

    std::string configName;
};
} // namespace GameSystem
