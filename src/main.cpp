#include "GameSystem/AppInstance.h"
#include "GameSystem/Exceptions.h"
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
    catch (GameSystem::CriticalException &exception)
    {
        std::cerr << exception.what() << "\n";
    }
    catch (GameSystem::InvalidDataException &exception)
    {
        std::cerr << "Unhendled InvalidDataException" << '\n';
        std::cerr << exception.what() << "\n";
    }
    catch (const std::exception &exception)
    {
        std::cerr << "Unknown exception" << '\n';
        std::cerr << exception.what() << '\n';
    }
}
