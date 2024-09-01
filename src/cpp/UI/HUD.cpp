#include "UI/HUD.h"
#include "GameSystem/Image.h"
#include "Types.h"
#include "UI/Canvas.h"
#include <memory>

namespace UI
{
HUD::HUD(const Vector2D &screenSize) : Canvas(Vector2D{0., 0.})
{
    background =
        std::make_shared<GameSystem::Image>("resurces/textures/HUDBackground.png", screenSize, Vector2D(0., 0.));
}

void HUD::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    background->Draw(inRenderer);
    Canvas::Draw(inRenderer);
}
} // namespace UI