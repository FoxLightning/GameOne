#pragma once
#include "UI/CanvasSlot.h"
#include <memory>

namespace GameSystem
{
class TextBlock;
};

namespace UI
{
class IntegrityWidget : public CanvasSlot, public std::enable_shared_from_this<IntegrityWidget>
{
  public:
    explicit IntegrityWidget(const std::string &configPath);
    void Init();

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double inDeltaTime) override {};

  private:
    [[nodiscard]] auto GetIntegritySymbolString(uint64_t integrity) -> std::string;

    std::shared_ptr<GameSystem::TextBlock> widgetName;
    std::shared_ptr<GameSystem::TextBlock> integrity;

    std::string integrityString;
    char integritySymbol = 0;

    uint64_t currentScore = 0;
};
} // namespace UI