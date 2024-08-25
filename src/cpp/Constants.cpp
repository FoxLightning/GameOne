#include "Constants.h"
#include "Types.h"
#include <cstdint>

namespace Const
{
namespace Color
{
const LinearColor Black = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
const LinearColor Red = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
const LinearColor Green = {.r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF};
const LinearColor Blue = {.r = 0x00, .g = 0x00, .b = 0xFF, .a = 0xFF};
} // namespace Color
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
namespace Sound
{
const char *const shipRocketLounch = "resurces/sound/rocket_launch.wav";
const char *const enemyHit = "resurces/sound/enemy_hit.wav";
const char *const enemyExplosion = "resurces/sound/enemy_explosion.wav";
} // namespace Sound
namespace Prototype
{
namespace Entity
{
const char *const enemyEntity = "resurces/Asset/Entity/EnemyEntity.json";
const char *const missleEntity = "resurces/Asset/Entity/MissleEntity.json";
const char *const playerShipEntity = "resurces/Asset/Entity/PlayerShipEntity.json";
} // namespace Entity
namespace Animation
{
const char *const enemyDamageAnimation = "resurces/Asset/Animation/EnemyDamageAnimation.json";
const char *const enemyIdleAnimation = "resurces/Asset/Animation/EnemyIdleAnimation.json";
const char *const enemyExplosionAnimation = "resurces/Asset/Animation/EnemyExplosionAnimation.json";
const char *const missleExplosionAnimation = "resurces/Asset/Animation/MissleExplosionAnimation.json";
} // namespace Animation
} // namespace Prototype
} // namespace Const
