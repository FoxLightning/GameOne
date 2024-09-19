#include "UI/Menu.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "UI/SubMenu.h"
#include <cassert>
#include <memory>

namespace UI
{

Menu::Menu()
{
    focusedMenu = std::make_shared<SubMenu>(this, "resurces/Asset/UI/PauseMenuWidget.json");
    focusedMenu->Init();
    subMenuStack.emplace_back(focusedMenu);
}

void Menu::Update(double deltaTime)
{
    UpdatePop();
    UpdateToAdd();
    if (subMenuStack.empty())
    {
        GameSystem::AppInstance::PopState();
        return;
    }
    if (focusedMenu != subMenuStack.back())
    {
        focusedMenu->Deinit();
        focusedMenu = subMenuStack.back();
        focusedMenu->Init();
    }
    focusedMenu->Update(deltaTime);
}

void Menu::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    if (!subMenuStack.empty())
    {
        subMenuStack.back()->Draw(inRenderer);
    }
}

void Menu::UpdatePop()
{
    assert(subMenuStack.size() >= toPop);
    subMenuStack.erase(subMenuStack.end() - toPop, subMenuStack.end());
    toPop = 0;
}

void Menu::UpdateToAdd()
{
    subMenuStack.append_range(subMenuToAdd);
    subMenuToAdd.clear();
}

} // namespace UI