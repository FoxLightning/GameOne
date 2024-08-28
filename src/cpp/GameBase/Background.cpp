#include "GameBase/Background.h"
#include "GameBase/BackgroundLayer.h"
#include "GameSystem/Image.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace GameBase
{

void Background::Update(double deltaTime)
{
    for (const std::shared_ptr<BackgroundLayer> &layer : parallaxLayers)
    {
        layer->Update(deltaTime);
    }
}

void Background::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    for (const std::shared_ptr<BackgroundLayer> &layer : parallaxLayers)
    {
        layer->Draw(inRenderer);
    }
}

Background::Background(const std::string &configName, const Vector2D &inSize)
{
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(configName, tree);

    for (const auto &backgroundLevelConfig : tree)
    {

        const auto &speed = backgroundLevelConfig.second.get<double>("speed");
        std::vector<std::shared_ptr<GameSystem::Image>> imageList;
        auto textureConfig = backgroundLevelConfig.second.get_child("textures");
        imageList.reserve(textureConfig.size());

        for (const auto &texture : textureConfig)
        {
            imageList.push_back(std::make_shared<GameSystem::Image>(
                texture.second.get_value<std::string>(), Vector2D{inSize.x(), inSize.x()}, Vector2D{0., 0.}));
        }

        parallaxLayers.push_back(std::make_shared<BackgroundLayer>(speed, inSize, std::move(imageList)));
    }
}
} // namespace GameBase