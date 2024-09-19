#include "UI/MenuButton.h"

#include "GameSystem/Renderer.h"
#include "GameSystem/TextBlock.h"
#include "Types.h"
#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace UI
{

MenuButton::MenuButton(const std::string &inText, const ButtonStyle &buttonStyle, const Vector2D &inPos,
                       const Vector2D &inPivot, std::function<void()> inAction)

    : buttonText(std::make_shared<GameSystem::TextBlock>(inText, buttonStyle.fontName, buttonStyle.size,
                                                         buttonStyle.color, inPos, inPivot)),
      defaultColor(buttonStyle.color), hoverColor(buttonStyle.inHoverColor), action(std::move(inAction))
{
}

void MenuButton::SetHover(bool shouldHover)
{
    buttonText->SetColor(shouldHover ? hoverColor : defaultColor);
}

void MenuButton::Execute()
{
    assert(action);
    action();
}

void MenuButton::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    buttonText->Draw(inRenderer);
}

} // namespace UI