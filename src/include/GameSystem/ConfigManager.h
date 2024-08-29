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
    auto GetDefaultConfiguration() -> Configuration;
    void LoadCurrentConfiguration();
    void LoadDefaultConfiguration();

  private:
    struct Configuration
    {
        Vector2I windowResolution{0, 0};
        double frameRate{0.};
    };
    Configuration configuration;
    Configuration defaultConfiguration;
};
}; // namespace GameSystem
