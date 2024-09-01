#include "UI/Canvas.h"
#include "Types.h"
#include "UI/CanvasSlot.h"
#include <algorithm>
#include <memory>

namespace UI
{

Canvas::Canvas(const Vector2D &inSize) : CanvasSlot::CanvasSlot(inSize)
{
}

void Canvas::Update(double deltaTime)
{
    for (const auto &child : children)
    {
        child->Update(deltaTime);
    }
    for (const auto &child : childrenToRemove)
    {
        auto range = std::ranges::remove_if(children, [child](const auto &A) -> bool {
            if (A)
            {
                return A == child;
            }
            return true;
        });
        children.erase(range.begin(), range.end());
    }
    children.append_range(childrenToAdd);
    childrenToAdd.clear();
    childrenToRemove.clear();
}

void Canvas::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    inRenderer->SetViewPosition(GetPosition());
    for (const auto &child : children)
    {
        child->Draw(inRenderer);
    }
    inRenderer->PopViewPosition();
}

void Canvas::AddChild(const std::shared_ptr<CanvasSlot> &child)
{
    childrenToAdd.push_back(child);
}

void Canvas::DeleteChild(const std::shared_ptr<CanvasSlot> &child)
{
    childrenToRemove.push_back(child);
}

} // namespace UI
