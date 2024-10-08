#include "UI/HUD.h"
#include "Constants.h"
#include "GameSystem/Image.h"
#include "Types.h"
#include "UI/Canvas.h"
#include "UI/IntegrityWidget.h"
#include "UI/ScoreWidget.h"
#include <memory>

namespace UI
{
HUD::HUD(const Vector2D &screenSize) : Canvas(Vector2D{0., 0.})
{
    background =
        std::make_shared<GameSystem::Image>("resurces/textures/HUDBackground.png", screenSize, Vector2D(0., 0.));

    const auto &scoreWidget = std::make_shared<ScoreWidget>(Const::Prototype::UI::scoreWidget);
    const auto &integrityWidget = std::make_shared<IntegrityWidget>(Const::Prototype::UI::integrityWidget);
    scoreWidget->Init();
    integrityWidget->Init();
    AddChild(scoreWidget);
    AddChild(integrityWidget);
}

void HUD::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    background->Draw(inRenderer);
    Canvas::Draw(inRenderer);
}
} // namespace UI