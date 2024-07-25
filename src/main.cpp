#include "GameSystem/AppInstance.h"
#include <exception>
#include <iostream>
#include <memory>

auto main(int /* argc */, char ** /* argv[] */) -> int
{
    try
    {
        auto gameInstance = std::make_shared<GameSystem::AppInstance>();
        gameInstance->Start();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
