#pragma once

#include "GameSystem/AppInstance.h"
#include "Types.h"

namespace GameBase
{
class GameWorld;

class Scenario : public GameSystem::IUpdateble
{
  public:
    Scenario() = default;
    void Update(double deltaTime) override;

  private:
    static void SpawnEnemies(const std::vector<Vector2D> &positions);
    static auto GetSpawnPositions(uint8_t positionsNum) -> std::vector<Vector2D>;

    double timeFromLastSpawn = 0.;
    double timeToSpawn = 3.;
    uint8_t spawnNumber = 5;
};

} // namespace GameBase