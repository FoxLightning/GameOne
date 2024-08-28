#pragma once
#include "Constants.h"
#include "Types.h"

namespace GameSystem
{
class ConfigManager
{
    struct Configuration;

  public:
    ConfigManager();

    auto GetConfiguration() -> Configuration;

  private:
    struct Configuration
    {
        Vector2I windowResolution{0, 0};
        double frameRate{0.};
    } configuration;
};
}; // namespace GameSystem
