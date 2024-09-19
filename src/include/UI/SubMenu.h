#pragma once
#include "GameSystem/InputManager.h"
#include "UI/Canvas.h"
#include "UI/MenuButton.h"

namespace GameSystem
{
class Image;
}

namespace UI
{
class Menu;
class MenuButton;

class SubMenu : public Canvas, public std::enable_shared_from_this<SubMenu>
{
  public:
    explicit SubMenu(Menu *inParent, std::string inConfigName);
    virtual void Init();
    virtual void Deinit();

    void HandleInput(GameSystem::EventType eventType, GameSystem::ActionType actionType);

    void ResumeFromPause();
    void PushMenu(const std::string &configName);

  private:
    std::string configName;

    void PressButton();
    void HoverButton(int64_t inIndex);
    static auto GetButtonStyle(const std::string &configName) -> ButtonStyle;
    std::shared_ptr<GameSystem::Image> backgroundImage;

    std::vector<std::shared_ptr<MenuButton>> buttonList;
    int64_t hoveredButtonIndex = 0;
    Menu *parent;
};
} // namespace UI