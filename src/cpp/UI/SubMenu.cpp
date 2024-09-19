#include "UI/SubMenu.h"
#include "GameSystem/EventManager.h"
#include "GameSystem/Image.h"
#include "GameSystem/InputManager.h"
#include "GameSystem/TextBlock.h"
#include "UI/Canvas.h"
#include "UI/CanvasSlot.h"
#include "UI/Menu.h"
#include "UI/MenuButton.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace UI
{

SubMenu::SubMenu(Menu *inParent, std::string inConfigName)
    : configName(std::move(inConfigName)), Canvas(Vector2D(0., 0.)), parent(inParent)
{

    boost::property_tree::ptree subViewTree;
    boost::property_tree::read_json(configName, subViewTree);
    backgroundImage = std::make_shared<GameSystem::Image>(
        subViewTree.get<std::string>("background"),
        Vector2D{subViewTree.get<double>("size.x"), subViewTree.get<double>("size.y")}, Vector2D(0., 0.));

    const auto padding = subViewTree.get<double>("padding");
    const Vector2D blockPos{subViewTree.get<double>("position.x"), subViewTree.get<double>("position.y")};

    const std::vector<std::string> options{"continue", "options", "exit"};
    SetPosition(blockPos);
    const ButtonStyle buttonStyle = GetButtonStyle(subViewTree.get<std::string>("buttonStyle"));

    double offset = 0.;
    for (const auto &option : subViewTree.get_child("buttonData"))
    {
        const Vector2D pos{0, offset};
        const Vector2D piv{0., 0.};
        auto buttonToAdd =
            std::make_shared<MenuButton>(option.second.get<std::string>("buttonName"), buttonStyle, pos, piv, [] {});
        AddChild(std::dynamic_pointer_cast<UI::CanvasSlot>(buttonToAdd));
        buttonList.push_back(buttonToAdd);
        offset += (buttonStyle.size + padding);
    }
    buttonList[0]->SetHover(true);
}

void SubMenu::Init()
{
    GameSystem::EventManager::SubscribeInput({

        .inputContext = GameSystem::InputContext::pause,
        .invoker = weak_from_this(),
        .callback = [this](GameSystem::EventType eventType, GameSystem::ActionType actionType) {
            HandleInput(eventType, actionType);
        }});
}

void SubMenu::Deinit()
{
    GameSystem::EventManager::UnsubscribeInput(weak_from_this());
}

void SubMenu::HoverButton(int64_t inIndex)
{
    assert(inIndex < buttonList.size());
    assert(inIndex >= 0);
    assert(inIndex != hoveredButtonIndex);

    buttonList[inIndex]->SetHover(true);
    buttonList[hoveredButtonIndex]->SetHover(false);
    hoveredButtonIndex = inIndex;
}

auto SubMenu::GetButtonStyle(const std::string &configName) -> ButtonStyle
{
    boost::property_tree::ptree buttonStyleTree;
    boost::property_tree::read_json(configName, buttonStyleTree);

    return ButtonStyle{
        .fontName = buttonStyleTree.get<std::string>("font"),
        .size = buttonStyleTree.get<int32_t>("size"),
        .color = {.r = buttonStyleTree.get<uint8_t>("defaultColor.r"),
                  .g = buttonStyleTree.get<uint8_t>("defaultColor.g"),
                  .b = buttonStyleTree.get<uint8_t>("defaultColor.b"),
                  .a = buttonStyleTree.get<uint8_t>("defaultColor.a")},
        .inHoverColor = {.r = buttonStyleTree.get<uint8_t>("hoverColor.r"),
                         .g = buttonStyleTree.get<uint8_t>("hoverColor.g"),
                         .b = buttonStyleTree.get<uint8_t>("hoverColor.b"),
                         .a = buttonStyleTree.get<uint8_t>("hoverColor.a")},
    };
}

void SubMenu::HandleInput(GameSystem::EventType eventType, GameSystem::ActionType actionType)
{
    if (actionType == GameSystem::ActionType::Escape && eventType == GameSystem::EventType::Stop)
    {
        parent->Pop();
        return;
    }
    if (actionType == GameSystem::ActionType::MoveDown && eventType == GameSystem::EventType::Stop)
    {
        if (buttonList.size() - 1 != hoveredButtonIndex)
        {
            HoverButton(hoveredButtonIndex + 1);
        }
    }
    if (actionType == GameSystem::ActionType::MoveUp && eventType == GameSystem::EventType::Stop)
    {
        if (0 != hoveredButtonIndex)
        {
            HoverButton(hoveredButtonIndex - 1);
        }
    }
    if (actionType == GameSystem::ActionType::MainAction && eventType == GameSystem::EventType::Stop)
    {
        PressButton();
    }
}

void SubMenu::PressButton()
{
    buttonList[hoveredButtonIndex]->Execute();
}

} // namespace UI