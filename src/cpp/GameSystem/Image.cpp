#include "GameSystem/Image.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace GameSystem
{
Image::Image(std::string inName) : configName(std::move(inName))
{
    boost::property_tree::ptree imageAssetTree;
    boost::property_tree::read_json(configName, imageAssetTree);

    const std::shared_ptr<ResurceManager> resurceManager = AppInstance::GetResurceManager();
    texture = resurceManager->GetTexture(imageAssetTree.get<std::string>("texturePath"));

    size.x(imageAssetTree.get<double>("size.x"));
    size.y(imageAssetTree.get<double>("size.y"));
    pivot.x(imageAssetTree.get<double>("pivot.x"));
    pivot.y(imageAssetTree.get<double>("pivot.y"));

    std::cout << std::format("Image prototype created from config: \"{}\".\n", configName);
}
auto Image::GetSize() const -> const Vector2D &
{
    return size;
}

void Image::SetPos(const Vector2D &inPos)
{
    pos = inPos;
}

auto Image::GetPos() const -> const Vector2D &
{
    return pos;
}

void Image::Draw(std::shared_ptr<Renderer> inRenderer)
{
    const Vector2D min{pos.x() - (size.x() * pivot.x()), pos.y() - (size.y() * pivot.y())};
    const Vector2D max{pos.x() + (size.x() * (1. - pivot.x())), pos.y() + (size.y() * (1 - pivot.y()))};
    inRenderer->Draw(Box2D(min, max), texture);
}
} // namespace GameSystem
