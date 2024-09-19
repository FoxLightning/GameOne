#include "UI/ButtonActionHolder.h"
#include "UI/SubMenu.h"
#include <map>

namespace UI
{

auto ButtonActionHolder::GetAction(const std::string &actionName, SubMenu *subMenu) -> std::function<void()>
{
    static const std::map<std::string, std::function<void(SubMenu *)>> actionMap{
        {"resume", [](SubMenu *subMenu) { subMenu->ResumeFromPause(); }},
        {"exitGame", [](SubMenu *subMenu) { exit(0); }}};

    if (!actionMap.contains(actionName))
    {
        return nullptr;
    }
    return [subMenu, actionName]() { actionMap.at(actionName)(subMenu); };
}
} // namespace UI