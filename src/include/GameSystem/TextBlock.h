#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"

namespace GameSystem
{
class Image;
class Font;

class TextBlock : IRendereble
{
  public:
    TextBlock(std::string inText, const std::string &fontName, int32_t size, const LinearColor &color,
              const Vector2D &inPos, const Vector2D &inPivot);
    void SetText(const std::string &inText);
    void Draw(std::shared_ptr<Renderer> inRenderer) override;

  private:
    void GenerateTextImage(const std::string &inText);

    std::string text;
    LinearColor color;
    Vector2D pos;
    Vector2D pivot;
    std::shared_ptr<Image> textImage;
    std::shared_ptr<Font> font;
};
} // namespace GameSystem