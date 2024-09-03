#include "UI/ScoreWidget.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/TextBlock.h"
#include "Types.h"
#include "UI/CanvasSlot.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cstdint>
#include <format>
#include <memory>
#include <string>

namespace UI
{

ScoreWidget::ScoreWidget(const std::string &inConfigName) : CanvasSlot(Vector2D(0., 0.))
{
    boost::property_tree::ptree scoreAssetTree;
    boost::property_tree::read_json(inConfigName, scoreAssetTree);

    const auto scoreText = scoreAssetTree.get<std::string>("text");
    const auto fontText = scoreAssetTree.get<std::string>("fontText");
    const auto fontScore = scoreAssetTree.get<std::string>("fontScore");
    const auto fontSize = scoreAssetTree.get<int32_t>("fontSize");
    const LinearColor fontColor{.r = scoreAssetTree.get<uint8_t>("fontColor.r"),
                                .g = scoreAssetTree.get<uint8_t>("fontColor.g"),
                                .b = scoreAssetTree.get<uint8_t>("fontColor.b"),
                                .a = 255};
    const Vector2D position{scoreAssetTree.get<double>("position.x"), scoreAssetTree.get<double>("position.y")};

    textBlock =
        std::make_shared<GameSystem::TextBlock>(scoreText, fontText, fontSize, fontColor, position, Vector2D(0., 0.));
    scoreBlock = std::make_shared<GameSystem::TextBlock>(
        GetScoreText(), fontScore, fontSize, fontColor,
        Vector2D{position.x(), position.y() + static_cast<double>(fontSize)}, Vector2D(0., 0.));
}
void ScoreWidget::Init()
{
    GameSystem::EventManager::SubscribeEnemyDeath({.invoker = weak_from_this(), .callback = [this](uint64_t reward) {
                                                       currentScore += reward;
                                                       scoreBlock->SetText(GetScoreText());
                                                   }});
}

void ScoreWidget::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    textBlock->Draw(inRenderer);
    scoreBlock->Draw(inRenderer);
}

auto ScoreWidget::GetScoreText() -> std::string
{
    return std::format("{:07}", currentScore);
}

} // namespace UI