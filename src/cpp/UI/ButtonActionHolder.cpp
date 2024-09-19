#include "UI/ButtonActionHolder.h"
#include "UI/SubMenu.h"
#include <cstdlib>
#include <functional>
#include <map>
#include <string>

namespace UI
{

auto ButtonActionHolder::GetAction(const std::string &actionName, SubMenu *subMenu) -> std::function<void()>
{
    return GetAction(actionName, subMenu, "");
}

auto ButtonActionHolder::GetAction(const std::string &actionName, SubMenu *subMenu,
                                   const std::string &data) -> std::function<void()>
{
    static const std::map<std::string, std::function<void(SubMenu *, const std::string &)>> actionMap{
        {"resume", [](SubMenu *subMenu, const std::string & /*data*/) { subMenu->ResumeFromPause(); }},
        {"goTo", [](SubMenu *subMenu, const std::string &data) { subMenu->PushMenu(data); }},
        {"exitGame", [](SubMenu * /*subMenu*/, const std::string & /*data*/) { exit(0); }}};

    if (!actionMap.contains(actionName))
    {
        return nullptr;
    }
    return [subMenu, actionName, data]() { actionMap.at(actionName)(subMenu, data); }; // nolint
}
} // namespace UI