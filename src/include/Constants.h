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
namespace Geometry
{
extern const double enemySize;
extern const double playerSize;
extern const double bulletSize;
} // namespace Geometry
} // namespace System
namespace Gameplay
{
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
namespace Sound
{
extern const char *const shipRocketLounch;
extern const char *const enemyHit;
extern const char *const enemyExplosion;
} // namespace Sound
namespace Prototype
{
namespace Entity
{
extern const char *const enemyEntity;
extern const char *const missleEntity;
extern const char *const playerShipEntity;
} // namespace Entity
namespace Animation
{
extern const char *const enemyIdleAnimation;
extern const char *const enemyDamageAnimation;
extern const char *const enemyExplosionAnimation;
extern const char *const missleExplosionAnimation;
} // namespace Animation
} // namespace Prototype
} // namespace Const
