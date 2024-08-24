#include "GameSystem/BaseAnimation.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace GameSystem
{

BaseAnimation::BaseAnimation(const std::string &name) : tileSize(), tiles()
{
    boost::property_tree::ptree animaitonAssetTree;
    boost::property_tree::read_json(name, animaitonAssetTree);

    const std::shared_ptr<ResurceManager> &resurceManager = AppInstance::GetResurceManager();
    atlas = resurceManager->GetTexture(animaitonAssetTree.get<std::string>("atlas"));
    tileSize.x(animaitonAssetTree.get_child("tileSize").get<double>("x"));
    tileSize.y(animaitonAssetTree.get_child("tileSize").get<double>("y"));
    frames = animaitonAssetTree.get<int64_t>("frames");
    frameTime = 1. / animaitonAssetTree.get<double>("fps");
    tiles.x(animaitonAssetTree.get_child("tiles").get<int32_t>("x"));
    tiles.y(animaitonAssetTree.get_child("tiles").get<int32_t>("y"));
    pivot.x(animaitonAssetTree.get_child("pivot").get<double>("x"));
    pivot.y(animaitonAssetTree.get_child("pivot").get<double>("y"));
    size.x(animaitonAssetTree.get_child("size").get<int32_t>("x"));
    size.y(animaitonAssetTree.get_child("size").get<int32_t>("y"));
}

void BaseAnimation::Update(double deltaTime)
{
    assert(!isFinished);
    if (currentTime >= (frameTime * static_cast<double>(frames)))
    {
        isFinished = true;
        if (onAnimationFinished)
        {
            onAnimationFinished();
        }
        return;
    }
    currentTime += deltaTime;
}

void BaseAnimation::Draw(std::shared_ptr<Renderer> inRenderer)
{
    const auto currentFrame = static_cast<int64_t>(currentTime / frameTime);

    const float xPos = static_cast<float>(currentFrame % tiles.x()) * static_cast<float>(tileSize.x());
    const float yPos = static_cast<float>(currentFrame / tiles.y()) * static_cast<float>(tileSize.y()); // NOLINT
    const auto wSize = static_cast<float>(tileSize.x());
    const auto hSize = static_cast<float>(tileSize.y());
    const Box2D atlasBox{{xPos, yPos}, {xPos + wSize, yPos + hSize}};
    const Box2D destinationBox{{pos.x() - (size.x() * pivot.x()), pos.y() - (size.y() * pivot.y())},
                               {pos.x() + (size.x() * (1. - pivot.x())), pos.y() + (size.y() * (1 - pivot.y()))}};
    inRenderer->Draw(destinationBox, atlasBox, atlas);
}

void BaseAnimation::SetPosition(const Vector2D &inPos)
{
    pos = inPos;
}

auto BaseAnimation::IsAnimationFinished() const -> bool
{
    return isFinished;
}

void BaseAnimation::BindOnAnimationFinished(std::function<void()> callback)
{
    onAnimationFinished = std::move(callback);
}

} // namespace GameSystem