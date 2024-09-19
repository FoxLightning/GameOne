#pragma once
#include <functional>

namespace UI
{
class SubMenu;

class ButtonActionHolder
{
  public:
    static auto GetAction(const std::string &actionName, SubMenu *subMenu) -> std::function<void()>;
    static auto GetAction(const std::string &actionName, SubMenu *subMenu,
                          const std::string &data) -> std::function<void()>;
};
} // namespace UI