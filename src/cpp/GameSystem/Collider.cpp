#include "GameSystem/Collider.h"
#include "Types.h"

namespace GameSystem
{
auto Collider::GetRectangle() const -> const Box2D &
{
    return rectangle;
}

auto Collider::GetPosition() const -> Vector2D
{
    return rectangle.min_corner() + (rectangle.max_corner() - rectangle.min_corner()) / 2.;
}

auto Collider::GetDesiredRectangle() const -> const Box2D &
{
    return desiredRectangle;
}

auto Collider::GetSpeedToApply() -> Vector2D
{
    return speedToApply;
}

void Collider::SetSize(Vector2D inSize)
{
    const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();
    const double curPosX = rectangle.min_corner().x() + (curSize.x() * pivot.x());
    const double curPosY = rectangle.min_corner().y() + (curSize.y() * pivot.y());

    const double leftPadding = inSize.x() * pivot.x();
    const double RightPadding = inSize.x() - leftPadding;
    const double topPadding = inSize.y() * pivot.y();
    const double bottomPadding = inSize.y() - topPadding;

    rectangle = Box2D(Vector2D(curPosX - leftPadding, curPosY - topPadding),
                      Vector2D(curPosX + RightPadding, curPosY + bottomPadding));
}

void Collider::SetPosition(Vector2D inPosition)
{
    const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();

    const double leftPadding = curSize.x() * pivot.x();
    const double RightPadding = curSize.x() - leftPadding;
    const double topPadding = curSize.y() * pivot.y();
    const double bottomPadding = curSize.y() - topPadding;

    desiredRectangle = Box2D(Vector2D(inPosition.x() - leftPadding, inPosition.y() - topPadding),
                             Vector2D(inPosition.x() + RightPadding, inPosition.y() + bottomPadding));
}

void Collider::SetPivot(Vector2D inPivot, bool updateRectangle)
{
    pivot = inPivot;
    if (updateRectangle)
    {
        const Vector2D curSize = rectangle.max_corner() - rectangle.min_corner();
        const double curPosX = rectangle.min_corner().x() + (curSize.x() * pivot.x());
        const double curPosY = rectangle.min_corner().y() + (curSize.y() * pivot.y());

        const double leftPadding = curSize.x() * pivot.x();
        const double RightPadding = curSize.x() - leftPadding;
        const double topPadding = curSize.y() * pivot.y();
        const double bottomPadding = curSize.y() - topPadding;

        rectangle = Box2D(Vector2D(curPosX - leftPadding, curPosY - topPadding),
                          Vector2D(curPosX + RightPadding, curPosY + bottomPadding));
    }
}

void Collider::TryMove(Vector2D delta)
{
    speedToApply = delta;
    desiredRectangle = rectangle + speedToApply;
}

void Collider::ApplyDesiredPosition()
{
    rectangle = desiredRectangle;
}
} // namespace GameSystem