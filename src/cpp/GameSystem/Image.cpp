#include "GameSystem/Image.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/ResurceManager.h"
#include "Types.h"
#include <cassert>
#include <memory>

namespace GameSystem
{

Image::Image(const char *inPath, Vector2D inPos, Vector2D inSize, Vector2D inPivot)
    : path(inPath), pos(inPos), size(inSize), pivot(inPivot)
{
    assert(pivot.x() >= 0. && pivot.x() <= 1.);
    assert(pivot.y() >= 0. && pivot.y() <= 1.);
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
    inRenderer->Draw(Box2D(min, max), resManager->GetTexture(path));
}
} // namespace GameSystem
