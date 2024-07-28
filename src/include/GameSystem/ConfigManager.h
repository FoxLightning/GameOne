#pragma once

#include "Types.h"

namespace GameSystem
{
// TODO get this data from config
class ConfigManager
{
  public:
    ConfigManager() = default;
    Vector2L windowResolution = {1280L, 720L};
    double frameRate = 120.;
};
}; // namespace GameSystem
