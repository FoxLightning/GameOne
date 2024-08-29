#include "GameSystem/ConfigManager.h"
#include "Constants.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cstdint>

namespace GameSystem
{
ConfigManager::ConfigManager()
{
    LoadCurrentConfiguration();
    LoadDefaultConfiguration();
}

void ConfigManager::LoadCurrentConfiguration()
{
    boost::property_tree::ptree settingsTree;
    boost::property_tree::read_json(Const::AssetPaths::appConfig, settingsTree);
    configuration.frameRate = settingsTree.get<double>("frameRate");
    configuration.windowResolution =
        Vector2I{settingsTree.get<int32_t>("resolution.x"), settingsTree.get<int32_t>("resolution.y")};
}

void ConfigManager::LoadDefaultConfiguration()
{
    boost::property_tree::ptree settingsTree;
    boost::property_tree::read_json(Const::AssetPaths::defaultAppConfig, settingsTree);
    defaultConfiguration.frameRate = settingsTree.get<double>("frameRate");
    defaultConfiguration.windowResolution =
        Vector2I{settingsTree.get<int32_t>("resolution.x"), settingsTree.get<int32_t>("resolution.y")};
}

auto ConfigManager::GetConfiguration() -> Configuration
{
    return configuration;
}

auto ConfigManager::GetDefaultConfiguration() -> Configuration
{
    return defaultConfiguration;
}
} // namespace GameSystem