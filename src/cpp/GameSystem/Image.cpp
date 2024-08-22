#include "GameSystem/Image.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/Texture.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <cassert>
#include <memory>
#include <string>
#include <utility>

namespace GameSystem
{
const char *const sizeField = "size";
const char *const pivotField = "pivot";
const char *const textureField = "texturePath";

Image::Image(std::shared_ptr<Texture> inTexture, Vector2D inPos, Vector2D inSize, Vector2D inPivot)
    : texture(std::move(inTexture)), pos(inPos), size(inSize), pivot(inPivot)
{
    assert(pivot.x() >= 0. && pivot.x() <= 1.);
    assert(pivot.y() >= 0. && pivot.y() <= 1.);
}

Image::Image(const std::string &name)
{
    boost::property_tree::ptree imageAssetTree;
    boost::property_tree::read_json(name, imageAssetTree);

    texture = AppInstance::GetResurceManager()->GetTexture(imageAssetTree.get<std::string>(textureField)).lock();

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
    const std::shared_ptr<ResurceManager> &resManager = AppInstance::GetResurceManager();
    const Vector2D min{pos.x() - (size.x() * pivot.x()), pos.y() - (size.y() * pivot.y())};
    const Vector2D max{pos.x() + (size.x() * (1. - pivot.x())), pos.y() + (size.y() * (1 - pivot.y()))};
    inRenderer->Draw(Box2D(min, max), texture->GetTexture());
}
} // namespace GameSystem
