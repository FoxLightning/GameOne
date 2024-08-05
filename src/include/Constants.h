#pragma once
#include <cstdint>

namespace Const
{
namespace Color
{
extern const uint8_t chenelFull;
}
namespace System
{
extern const double bulletLifeTime;
namespace Geometry
{
extern const double center;
extern const double enemySize;
extern const double playerSize;
extern const double bulletSize;
} // namespace Geometry
} // namespace System
namespace Gameplay
{
extern const double playerMaxSpeed;
extern const double bulletSpeed;
extern const double playerReloadTime;
extern const double timeToSpawnEnemy;
extern const int64_t waveNumber;
} // namespace Gameplay
namespace Configuration
{
extern const char *const filePath;
namespace Fields
{
extern const char *const resolution;
extern const char *const resolutionWidth;
extern const char *const resolutionHeight;
extern const char *const frameRate;
} // namespace Fields
namespace Defaults
{
extern const int32_t resolutionWidth;
extern const int32_t resolutionHeight;
extern const double frameRate;
} // namespace Defaults
} // namespace Configuration
namespace Textures
{
extern const char *const ship;
extern const char *const enemy;
extern const char *const missle;
} // namespace Textures
} // namespace Const
