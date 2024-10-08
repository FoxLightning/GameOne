#include "Constants.h"
#include "Types.h"
#include <cstdint>

namespace Const
{
namespace Color
{
const LinearColor White = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
const LinearColor Black = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xFF};
const LinearColor Red = {.r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF};
const LinearColor Green = {.r = 0x00, .g = 0xFF, .b = 0x00, .a = 0xFF};
const LinearColor Blue = {.r = 0x00, .g = 0x00, .b = 0xFF, .a = 0xFF};
} // namespace Color
namespace System
{
const double bulletLifeTime = 10.;
} // namespace System
namespace Gameplay
{
const uint64_t maxIntegrity = 6;
const double timeToSpawnEnemy = 3.;
const int64_t waveNumber = 3;
} // namespace Gameplay
namespace Sound
{
const char *const shipRocketLounch = "resurces/sound/rocket_launch.wav";
const char *const enemyHit = "resurces/sound/enemy_hit.wav";
const char *const enemyExplosion = "resurces/sound/enemy_explosion.wav";
const char *const shitHit = "resurces/sound/ShipDamage.wav";
} // namespace Sound
namespace AssetPaths
{
const char *const gameWorld = "resurces/Asset/World/GameWorldAsset.json";
const char *const defaultAppConfig = "resurces/Asset/World/DefaultAppConfigAsset.json";
const char *const appConfig = "resurces/Config/AppConfig.json";
const char *const defaultConfig = "resurces/Asset/World/DefaultAppConfigAsset.json";
const char *const controls = "resurces/Config/ControlsConfig.json";
const char *const defaultControls = "resurces/Asset/World/DefaultControlsConfig.json";
} // namespace AssetPaths
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
namespace World
{
const char *const background = "resurces/Asset/World/BackgroundAsset.json";
} // namespace World
namespace UI
{
const char *const scoreWidget = "resurces/Asset/UI/ScoreWidget.json";
const char *const integrityWidget = "resurces/Asset/UI/IntegrityWidget.json";
} // namespace UI
} // namespace Prototype
} // namespace Const
