#pragma once

#include "Constants.h"
#include "Types.h"

namespace GameSystem
{
// get this data from config NOLINT
class ConfigManager
{
    struct Configuration;

  public:
    ConfigManager();

    auto GetConfiguration() -> Configuration;

  private:
    struct Configuration
    {
        Vector2I windowResolution{Const::Configuration::Defaults::resolutionWidth,
                                  Const::Configuration::Defaults::resolutionHeight};
        double frameRate{Const::Configuration::Defaults::frameRate};
    } configuration;
};
}; // namespace GameSystem
