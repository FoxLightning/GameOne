#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "UI/CanvasSlot.h"
#include "UI/MenuButtonBase.h"
#include <memory>

namespace GameSystem
{
class TextBlock;
}

namespace UI
{
struct ButtonStyle
{
    std::string fontName;
    int32_t size;
    LinearColor color;
    LinearColor inHoverColor;
};

class MenuButton : public MenuButtonBase
{
  public:
    MenuButton(const std::string &inText, const ButtonStyle &buttonStyle, const Vector2D &inPos,
               const Vector2D &inPivot);
    void SetHover(bool shouldHover) override;

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override {};

  private:
    std::shared_ptr<GameSystem::TextBlock> buttonText;

    LinearColor hoverColor;
    LinearColor defaultColor;
};
} // namespace UI