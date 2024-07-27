#include "GameBase/GameState.h"
#include <iostream>

namespace GameBase
{

GameState::GameState()
{
    std::cout << "GameState init\n";
}

void GameState::Update(double deltaTime)
{
}
} // namespace GameBase
