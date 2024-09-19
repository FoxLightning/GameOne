#pragma once
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "UI/CanvasSlot.h"
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

class MenuButton : public CanvasSlot
{
  public:
    MenuButton(const std::string &inText, const ButtonStyle &buttonStyle, const Vector2D &inPos,
               const Vector2D &inPivot, std::function<void()> inAction);
    void SetHover(bool shouldHover);
    void Execute();

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override {};

  private:
    std::shared_ptr<GameSystem::TextBlock> buttonText;
    std::function<void()> action;

    LinearColor hoverColor;
    LinearColor defaultColor;
};
} // namespace UI