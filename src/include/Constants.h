#pragma once
#include "Types.h"
#include <cstdint>

namespace Const
{
namespace Color
{
extern const LinearColor Black;
extern const LinearColor Red;
extern const LinearColor Green;
extern const LinearColor Blue;
} // namespace Color
namespace System
{
extern const double bulletLifeTime;
extern const double animationFrameTime;
extern const int64_t enemyDamageFrames;
extern const double explosionSize;
extern const double bulletExplosionSize;
extern const double explosionAnimationFrameTime;
extern const int64_t enemyExplosionFrames;
namespace Geometry
{
extern const double enemySize;
extern const double playerSize;
extern const double bulletSize;
} // namespace Geometry
} // namespace System
namespace Gameplay
{
extern const double playerMaxSpeed;
extern const double bulletSpeed;
extern const double enemySpeed;
extern const double playerReloadTime;
extern const double timeToSpawnEnemy;
extern const int64_t waveNumber;
extern const double bulletDamage;
extern const double enemyHP;
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
namespace Sound
{
extern const char *const shipRocketLounch;
extern const char *const enemyHit;
extern const char *const enemyExplosion;
} // namespace Sound
namespace Textures
{
extern const char *const ship;
extern const char *const enemy;
extern const char *const enemyAnimation;
extern const char *const enemyExplosionAnimation;
extern const char *const bulletExplosionAnimation;
extern const char *const missle;
} // namespace Textures
} // namespace Const
