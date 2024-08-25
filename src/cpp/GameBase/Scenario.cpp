#include "GameBase/Scenario.h"
#include "Constants.h"
#include "Game/Enemy.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/Exceptions.h"
#include "GameSystem/PrototypeHolder.h"
#include "Types.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

namespace GameBase
{

void Scenario::Update(double deltaTime)
{
    timeFromLastSpawn += deltaTime;
    if (timeFromLastSpawn > timeToSpawn)
    {
        timeFromLastSpawn = 0;
        SpawnEnemies(GetSpawnPositions(spawnNumber));
    }
}

void Scenario::SpawnEnemies(const std::vector<Vector2D> &positions)
{
    const std::shared_ptr<GameState> currentState = GameSystem::AppInstance::GetCurrentAppState();
    std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    if (!prototypeHolder)
    {
        throw GameSystem::CriticalException("prototype holder is not valid");
    }
    if (!currentState)
    {
        throw GameSystem::CriticalException("current game state is not valid");
    }
    const std::shared_ptr<GameWorld> gameWorld = currentState->GetGameWorld();
    if (!gameWorld)
    {
        throw GameSystem::CriticalException("current game world is not valid");
    }

    for (const Vector2D &position : positions)
    {
        std::shared_ptr<Game::Enemy> enemy = prototypeHolder->GetEnemy(Const::Prototype::Entity::enemyEntity);
        enemy->SetPosition(position);
        gameWorld->AddEntity(enemy);
    }
}
namespace
{
auto GetRandomPosInRange(double minPos, double maxPos)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minPos, maxPos);
    return dis(gen);
}

auto SearchLeft(std::vector<Vector2D>::iterator blockedItr, std::vector<Vector2D>::iterator start,
                double width) -> double
{
    double desiredPos = 0;
    do
    {
        desiredPos = blockedItr->x() - width;
        blockedItr--;
    } while (blockedItr >= start && std::abs(blockedItr->x() - desiredPos) < width);
    return desiredPos;
}

auto SearchRight(std::vector<Vector2D>::iterator blockedItr, std::vector<Vector2D>::iterator end,
                 double width) -> double
{
    double desiredPos = 0;
    do
    {
        desiredPos = blockedItr->x() + width;
        blockedItr++;
    } while (blockedItr < end && std::abs(blockedItr->x() - desiredPos) < width);
    return desiredPos;
}

auto IsInRange(double test, double min, double max) -> bool
{
    return test > min && test < max;
}

auto FindFreePosition(std::vector<Vector2D> blockedPositions, double minPos, double maxPos, double enemyWidth) -> double
{
    std::ranges::sort(blockedPositions,
                      [](const Vector2D &left, const Vector2D right) { return left.x() < right.x(); });

    double desiredPos = GetRandomPosInRange(minPos, maxPos);
    for (auto blockedItr = blockedPositions.begin(); blockedItr < blockedPositions.end(); blockedItr++)
    {
        if (std::abs(blockedItr->x() - desiredPos) > enemyWidth)
        {
            continue;
        }

        desiredPos = SearchLeft(blockedItr, blockedPositions.begin(), enemyWidth);
        if (IsInRange(desiredPos, minPos, maxPos))
        {
            return desiredPos;
        }

        desiredPos = SearchRight(blockedItr, blockedPositions.end(), enemyWidth);
        if (IsInRange(desiredPos, minPos, maxPos))
        {
            return desiredPos;
        }
        std::cerr << "No free space to spawn enemy.\n";
        break;
    }

    return desiredPos;
}
} // namespace
auto Scenario::GetSpawnPositions(int64_t positionsNum) -> std::vector<Vector2D>
{
    const double enemyWidth = 128.;
    const double enemyXPivot = 0.5;
    const double enemyYPivot = 0.5;
    const double yPos = -128. * enemyYPivot;

    const std::shared_ptr<GameSystem::ConfigManager> configManager = GameSystem::AppInstance::GetConfigManager();
    const Vector2I fieldSize = configManager->GetConfiguration().windowResolution;
    const double minPos = enemyWidth * enemyXPivot;
    const double maxPos = fieldSize.x() - (enemyWidth * enemyXPivot);

    std::vector<Vector2D> outList;
    for (int64_t i = 0; i < positionsNum; ++i)
    {
        const double xPos = FindFreePosition(outList, minPos, maxPos, enemyWidth);
        outList.emplace_back(xPos, yPos);
    }
    return outList;
}

} // namespace GameBase
