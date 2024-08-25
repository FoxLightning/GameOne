#include "GameBase/Background.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ConfigManager.h"
#include "GameSystem/PrototypeHolder.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <memory>
#include <string>
#include <utility>

namespace GameBase
{

void Background::Update(double deltaTime)
{
    curImage->SetPos({0, currentPosition});
    nextImage->SetPos({0, currentPosition - nextImage->GetSize().y()});
    currentPosition += speed * deltaTime;

    if (ShouldGenerateNewImage())
    {
        currentIndex = (currentIndex + 1) % imageList.size();
        currentPosition = currentPosition - nextImage->GetSize().y();

        curImage = std::move(nextImage);
        nextImage = imageList[(currentIndex + 1) % imageList.size()];
    }
}

void Background::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    nextImage->Draw(inRenderer);
    curImage->Draw(inRenderer);
}

auto Background::ShouldGenerateNewImage() -> bool
{
    const std::shared_ptr<GameSystem::ConfigManager> configManager = GameSystem::AppInstance::GetConfigManager();
    const Vector2I &resolution = configManager->GetConfiguration().windowResolution;
    return currentPosition > (curImage->GetSize().y() + resolution.y());
}

Background::Background(const std::string &configName)
{
    boost::property_tree::ptree backgroundAssetTree;
    boost::property_tree::read_json(configName, backgroundAssetTree);
    speed = backgroundAssetTree.get<double>("speed");

    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    for (const auto &item : backgroundAssetTree.get_child("imageList"))
    {
        imageList.push_back(prototypeHolder->GetImage(item.second.get_value<std::string>()));
    }

    curImage = imageList[currentIndex];
    nextImage = imageList[(currentIndex + 1) % imageList.size()];

    const std::shared_ptr<GameSystem::ConfigManager> configManager = GameSystem::AppInstance::GetConfigManager();
    const Vector2I &resolution = configManager->GetConfiguration().windowResolution;
    currentPosition = resolution.y();
    curImage->SetPos({0, currentPosition});
    nextImage->SetPos({0, currentPosition - curImage->GetSize().y()});
}
} // namespace GameBase