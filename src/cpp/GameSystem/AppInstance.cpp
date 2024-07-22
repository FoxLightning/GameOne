
#include <iostream>
#include "GameSystem/AppInstance.h"

GameSystem::AppInstance::AppInstance()
{
    std::cout << "Init\n";
}

GameSystem::AppInstance::~AppInstance()
{
    std::cout << "Deinit\n";
}

void GameSystem::AppInstance::Start()
{
    std::cout << "start\n";
}
