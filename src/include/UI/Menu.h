#pragma once
#include "UI/SubMenu.h"

namespace UI
{
class SubMenu;

class Menu : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    Menu();
    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    template <typename T, typename... Args>
    void Push(Args... args)
    {
        auto viewToAdd = std::dynamic_pointer_cast<SubMenu>(std::make_shared<T>(args...));
        subMenuStack.push_back(viewToAdd);
    }

    void Pop()
    {
        toPop++;
    }

  private:
    void UpdatePop();
    void UpdateToAdd();

    std::vector<std::shared_ptr<SubMenu>> subMenuStack;
    std::vector<std::shared_ptr<SubMenu>> subMenuToAdd;
    std::shared_ptr<SubMenu> focusedMenu;
    int64_t toPop = 0;
};

} // namespace UI