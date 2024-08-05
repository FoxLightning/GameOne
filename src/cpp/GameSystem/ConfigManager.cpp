#include "GameSystem/ConfigManager.h"
#include "Constants.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace GameSystem
{
ConfigManager::ConfigManager()
{
    boost::property_tree::ptree settingsTree;

    try
    {
        boost::property_tree::read_json(Const::Configuration::filePath, settingsTree);
    }
    catch (const boost::property_tree::json_parser::json_parser_error &e)
    {
        std::cerr << "Error reading JSON file: " << e.what() << std::endl;
        return;
    }

    try
    {
        configuration.frameRate = settingsTree.get<double>(Const::Configuration::Fields::frameRate);
        boost::property_tree::ptree resolution = settingsTree.get_child(Const::Configuration::Fields::resolution);
        auto height = resolution.get<int32_t>(Const::Configuration::Fields::resolutionHeight);
        auto width = resolution.get<int32_t>(Const::Configuration::Fields::resolutionWidth);
        configuration.windowResolution.x(width);
        configuration.windowResolution.y(height);
    }
    catch (const boost::property_tree::ptree_error &e)
    {
        std::cerr << "Error accessing data in JSON: " << e.what() << std::endl;
    }
}
auto ConfigManager::GetConfiguration() -> Configuration
{
    return configuration;
}
} // namespace GameSystem