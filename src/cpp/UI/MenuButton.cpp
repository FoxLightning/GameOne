#include "UI/MenuButton.h"

#include "GameSystem/Renderer.h"
#include "GameSystem/TextBlock.h"
#include "Types.h"
#include "UI/MenuButtonBase.h"
#include <cassert>
#include <memory>
#include <string>

namespace UI
{

MenuButton::MenuButton(const std::string &inText, const ButtonStyle &buttonStyle, const Vector2D &inPos,
                       const Vector2D &inPivot)

    : buttonText(std::make_shared<GameSystem::TextBlock>(inText, buttonStyle.fontName, buttonStyle.size,
                                                         buttonStyle.color, inPos, inPivot)),
      defaultColor(buttonStyle.color), hoverColor(buttonStyle.inHoverColor)
{
}

void MenuButton::SetHover(bool shouldHover)
{
    MenuButtonBase::SetHover(shouldHover);
    buttonText->SetColor(shouldHover ? hoverColor : defaultColor);
}

void MenuButton::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    buttonText->Draw(inRenderer);
}

} // namespace UI