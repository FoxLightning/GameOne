#pragma once
#include "Constants.h"
#include "GameSystem/AppInstance.h"
#include "Types.h"
#include <cstdint>

namespace GameBase
{
class GameWorld;

class Scenario : public GameSystem::IUpdateble
{
  public:
    explicit Scenario(const Vector2D &inFieldSize);
    void Update(double deltaTime) override;

  private:
    [[nodiscard]] auto GetSpawnPositions(int64_t positionsNum) const -> std::vector<Vector2D>;

    double timeFromLastSpawn = Const::Gameplay::timeToSpawnEnemy;
    double timeToSpawn = Const::Gameplay::timeToSpawnEnemy;
    uint8_t spawnNumber = Const::Gameplay::waveNumber;
    Vector2D fieldSize{0., 0.};
};

} // namespace GameBase