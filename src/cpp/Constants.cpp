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
const double animationFrameTime = 1. / 15.;
const int64_t enemyDamageFrames = 4;
const double explosionSize = 256.;
const double bulletExplosionSize = 128.;
const double explosionAnimationFrameTime = 1. / 15.;
const int64_t enemyExplosionFrames = 4;
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
const double enemySpeed = 100.;
const double playerReloadTime = 0.2;
const double timeToSpawnEnemy = 3.;
const int64_t waveNumber = 3;
const double bulletDamage = 1.;
const double enemyHP = 4.;
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
const char *const enemyAnimation = "resurces/textures/enemy_animation.png";
const char *const enemyExplosionAnimation = "resurces/textures/enemy_explosion.png";
const char *const bulletExplosionAnimation = "resurces/textures/bullet_explosion.png";
const char *const missle = "resurces/textures/Missile_A_Small.png";
} // namespace Textures
} // namespace Const
