#include "UI/CanvasSlot.h"
#include "Types.h"

namespace UI
{

CanvasSlot::CanvasSlot(Vector2D inPosition) : position(inPosition)
{
}

[[nodiscard]] auto CanvasSlot::GetPosition() const -> const Vector2D &
{
    return position;
}

void CanvasSlot::SetPosition(const Vector2D &inPosition)
{
    position = inPosition;
}

} // namespace UI
