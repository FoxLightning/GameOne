#include "UI/IntegrityWidget.h"
#include "Constants.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/TextBlock.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

namespace UI
{
IntegrityWidget::IntegrityWidget(const std::string &configPath)
{
    boost::property_tree::ptree integrityAssetTree;
    boost::property_tree::read_json(configPath, integrityAssetTree);

    const auto nameText = integrityAssetTree.get<std::string>("name");
    const auto nameFont = integrityAssetTree.get<std::string>("nameFont");
    const auto integitySymbolFont = integrityAssetTree.get<std::string>("integitySymbolFont");
    const auto fontSize = integrityAssetTree.get<int32_t>("fontSize");
    const LinearColor fontColor{.r = integrityAssetTree.get<uint8_t>("fontColor.r"),
                                .g = integrityAssetTree.get<uint8_t>("fontColor.g"),
                                .b = integrityAssetTree.get<uint8_t>("fontColor.b"),
                                .a = 255};
    integritySymbol = integrityAssetTree.get<char>("symbol");
    const Vector2D position{integrityAssetTree.get<double>("position.x"), integrityAssetTree.get<double>("position.y")};

    widgetName =
        std::make_shared<GameSystem::TextBlock>(nameText, nameFont, fontSize, fontColor, position, Vector2D(0., 0.));
    const double integrityPadding = 10.;
    integrity = std::make_shared<GameSystem::TextBlock>(
        GetIntegritySymbolString(Const::Gameplay::maxIntegrity), integitySymbolFont, fontSize, fontColor,
        Vector2D{position.x(), position.y() + static_cast<double>(fontSize) + integrityPadding}, Vector2D(0., 0.));

    integrityString.resize(Const::Gameplay::maxIntegrity);
}

void IntegrityWidget::Init()
{
    GameSystem::EventManager::SubscribePlayerShipIntegrityChange(
        {.invoker = weak_from_this(),
         .callback = [this](uint64_t inIntegrity) { integrity->SetText(GetIntegritySymbolString(inIntegrity)); }});
}

auto IntegrityWidget::GetIntegritySymbolString(uint64_t integrity) -> std::string
{
    assert(integrity <= Const::Gameplay::maxIntegrity);
    assert(0 <= integrity);

    for (int64_t strIndex = 0; strIndex < Const::Gameplay::maxIntegrity; strIndex++)
    {
        integrityString[strIndex] = strIndex < integrity ? integritySymbol : ' ';
    }
    return integrityString;
}

void IntegrityWidget::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    widgetName->Draw(inRenderer);
    integrity->Draw(inRenderer);
}

} // namespace UI