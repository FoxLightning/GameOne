#include "Game/SideBorder.h"
#include "GameSystem/Collider.h"
#include "Types.h"

namespace Game
{
SideBorder::SideBorder(const Vector2D &worldSize, Side side)
{
    constexpr double borderWith = 100.;
    switch (side)
    {
    case Side::left: {
        SetPivot({1., 0.});
        SetSize({borderWith, worldSize.y()});
        break;
    }
    case Side::right: {
        SetPivot({0., 0.});
        SetPosition({worldSize.x(), 0.});
        SetSize({borderWith, worldSize.y()});
        break;
    }
    case Side::top: {
        SetPivot({0., 1.});
        SetSize({worldSize.x(), borderWith});
        break;
    }
    }
}
void SideBorder::CheckCollision(Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

} // namespace Game