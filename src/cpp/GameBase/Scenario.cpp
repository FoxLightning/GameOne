#include "GameBase/Scenario.h"
#include "Game/Enemy.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "Types.h"
#include <algorithm>
#include <cassert>
#include <random>

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
    std::shared_ptr<GameState> currentState = GameSystem::AppInstance::GetCurrentAppState();
    if (!currentState)
    {
        std::cerr << "current game state is not valid\n";
        return;
    }
    std::shared_ptr<GameWorld> gameWorld = currentState->GetGameWorld();
    if (!gameWorld)
    {
        std::cerr << "current game world is not valid\n";
        return;
    }

    for (const Vector2D &position : positions)
    {
        gameWorld->AddEntity<Game::Enemy>(position, 100.);
    }
}

auto Scenario::GetSpawnPositions(uint8_t positionsNum) -> std::vector<Vector2D>
{
    std::random_device rd;
    std::mt19937 gen(rd());

    const double enemyWidth = 128.;
    const double enemyXPivot = 0.5;
    const double enemyYPivot = 0.5;
    const double yPos = -128. * enemyYPivot;

    Vector2I fieldSize = GameSystem::AppInstance::GetConfigManager()->windowResolution;
    const double minPos = enemyWidth * enemyXPivot;
    const double maxPos = fieldSize.x() - (enemyWidth * enemyXPivot);
    std::uniform_real_distribution<> dis(minPos, maxPos);

    std::vector<Vector2D> outList;
    for (uint8_t i = 0; i < positionsNum; ++i)
    {
        double desiredPos = dis(gen);
        bool needLeftCheck = false;
        for (auto el : outList)
        {
            if (std::abs(el.x() - desiredPos) < enemyWidth)
            {
                assert(!needLeftCheck);
                if (el.x() + enemyWidth < maxPos)
                {
                    desiredPos = el.x() + enemyWidth;
                }
                else
                {
                    needLeftCheck = true;
                }
            }
        }
        if (needLeftCheck)
        {
            for (auto itr = outList.end() - 1; itr >= outList.begin(); itr--)
            {
                if (std::abs(itr->x() - desiredPos) < enemyWidth)
                {
                    if (desiredPos > minPos)
                    {
                        desiredPos = itr->x() - enemyWidth;
                    }
                    else
                    {
                        assert(false);
                    }
                }
            }
        }
        outList.emplace_back(desiredPos, yPos);
        std::ranges::sort(outList, [](const Vector2D &left, const Vector2D right) { return left.x() < right.x(); });
    }
    for (auto a : outList)
    {
        std::cout << a.x() << std::endl;
    }
    return outList;
}

} // namespace GameBase
