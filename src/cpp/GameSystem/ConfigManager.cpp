#include "GameSystem/ConfigManager.h"
#include "Constants.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/json_parser/error.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cstdint>
#include <iostream>

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
        std::cerr << "Error reading JSON file: " << e.what() << "\n";
        std::cerr << "Default settings applyed.\n";
        return;
    }

    try
    {
        configuration.frameRate = settingsTree.get<double>(Const::Configuration::Fields::frameRate);
        const boost::property_tree::ptree resolution = settingsTree.get_child(Const::Configuration::Fields::resolution);
        const auto height = resolution.get<int32_t>(Const::Configuration::Fields::resolutionHeight);
        const auto width = resolution.get<int32_t>(Const::Configuration::Fields::resolutionWidth);
        configuration.windowResolution.x(width);
        configuration.windowResolution.y(height);
    }
    catch (const boost::property_tree::ptree_error &e)
    {
        configuration.frameRate = Const::Configuration::Defaults::frameRate;
        configuration.windowResolution.x(Const::Configuration::Defaults::resolutionWidth);
        configuration.windowResolution.y(Const::Configuration::Defaults::resolutionHeight);

        std::cerr << "Error accessing data in JSON: " << e.what() << "\n";
        std::cerr << "Default settings applyed.\n";
    }
}
auto ConfigManager::GetConfiguration() -> Configuration
{
    return configuration;
}
} // namespace GameSystem