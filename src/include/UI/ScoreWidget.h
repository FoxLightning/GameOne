#pragma once
#include "UI/CanvasSlot.h"
#include <memory>

namespace GameSystem
{
class Renderer;
class TextBlock;
} // namespace GameSystem

namespace UI
{
class ScoreWidget : public CanvasSlot, public std::enable_shared_from_this<ScoreWidget>

{
  public:
    explicit ScoreWidget(const std::string &inConfigName);
    void Init();

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    void Update(double inDeltaTime) override {};

  private:
    auto GetScoreText() -> std::string;
    std::shared_ptr<GameSystem::TextBlock> textBlock;
    std::shared_ptr<GameSystem::TextBlock> scoreBlock;

    uint64_t currentScore = 0;
};
} // namespace UI