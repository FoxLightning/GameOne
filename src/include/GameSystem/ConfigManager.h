#pragma once

#include "Types.h"

namespace GameSystem
{
// get this data from config NOLINT
class ConfigManager
{
  public:
    ConfigManager() = default;
    Vector2I windowResolution = {1280L, 720L}; // NOLINT
    double frameRate = 30.;                    // NOLINT
};
}; // namespace GameSystem
