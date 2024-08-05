#include "Constants.h"
#include <cstdint>

namespace Const
{
namespace Color
{
const uint8_t chenelFull = 0xFF;
}
namespace System
{
const double bulletLifeTime = 10.;
namespace Geometry
{
const double center = 0.5;
const double enemySize = 128.;
const double playerSize = 128.;
const double bulletSize = 40.;
} // namespace Geometry
} // namespace System
namespace Gameplay
{
const double playerMaxSpeed = 400.;
const double bulletSpeed = 800.;
const double playerReloadTime = 0.2;
const double timeToSpawnEnemy = 3.;
const int64_t waveNumber = 3;
} // namespace Gameplay
namespace Configuration
{
const char *const filePath = "resurces/configuration/system_settings.json";
namespace Fields
{
const char *const resolution = "resolution";
const char *const resolutionWidth = "width";
const char *const resolutionHeight = "height";
const char *const frameRate = "frame_rate";
} // namespace Fields
namespace Defaults
{
const int32_t resolutionWidth = 1280;
const int32_t resolutionHeight = 720;
const double frameRate = 120.;
} // namespace Defaults
} // namespace Configuration
namespace Textures
{
const char *const ship = "resurces/textures/Ship_1_A_Small.png";
const char *const enemy = "resurces/textures/Enemy_1_A_Small.png";
const char *const missle = "resurces/textures/Missile_A_Small.png";
} // namespace Textures
} // namespace Const
