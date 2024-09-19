#pragma once
#include "Types.h"
#include <cstdint>

namespace Const
{
namespace Color
{
extern const LinearColor White;
extern const LinearColor Black;
extern const LinearColor Red;
extern const LinearColor Green;
extern const LinearColor Blue;
} // namespace Color
namespace System
{
extern const double bulletLifeTime;
} // namespace System
namespace Gameplay
{
extern const uint64_t maxIntegrity;
extern const double timeToSpawnEnemy;
extern const int64_t waveNumber;
} // namespace Gameplay
namespace Sound
{
extern const char *const shipRocketLounch;
extern const char *const enemyHit;
extern const char *const enemyExplosion;
extern const char *const shitHit;
} // namespace Sound
namespace AssetPaths
{
extern const char *const gameWorld;
extern const char *const defaultAppConfig;
extern const char *const appConfig;
extern const char *const defaultConfig;
extern const char *const controls;
extern const char *const defaultControls;
} // namespace AssetPaths
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
namespace World
{
extern const char *const background;
} // namespace World
namespace UI
{
extern const char *const scoreWidget;
extern const char *const integrityWidget;
} // namespace UI
} // namespace Prototype
} // namespace Const
