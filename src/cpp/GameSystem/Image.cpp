#include "GameSystem/Image.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "GameSystem/ResurceManager.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <memory>
#include <string>

namespace GameSystem
{
const char *const sizeField = "size";
const char *const pivotField = "pivot";
const char *const textureField = "texturePath";

Image::Image(const std::string &name)
{
    boost::property_tree::ptree imageAssetTree;
    boost::property_tree::read_json(name, imageAssetTree);

    const std::shared_ptr<ResurceManager> resurceManager = AppInstance::GetResurceManager();
    texture = resurceManager->GetTexture(imageAssetTree.get<std::string>(textureField));

    size.x(imageAssetTree.get_child(sizeField).get<double>("x"));
    size.y(imageAssetTree.get_child(sizeField).get<double>("y"));
    pivot.x(imageAssetTree.get_child(pivotField).get<double>("x"));
    pivot.y(imageAssetTree.get_child(pivotField).get<double>("y"));
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
