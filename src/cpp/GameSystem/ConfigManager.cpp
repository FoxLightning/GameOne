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
    boost::property_tree::ptree settingsTree;
    boost::property_tree::read_json(Const::AssetPaths::appConfig, settingsTree);
    configuration.frameRate = settingsTree.get<double>("frameRate");
    configuration.windowResolution =
        Vector2I{settingsTree.get<int32_t>("resolution.x"), settingsTree.get<int32_t>("resolution.y")};
}
auto ConfigManager::GetConfiguration() -> Configuration
{
    return configuration;
}
} // namespace GameSystem