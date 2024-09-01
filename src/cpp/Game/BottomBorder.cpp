#include "Game/BottomBorder.h"
#include "GameSystem/Collider.h"
#include "Types.h"

namespace Game
{
BottomBorder::BottomBorder(const Vector2D &worldSize)
{
    constexpr double borderWith = 100.;
    SetPivot({0., 0.});
    SetPosition({0., worldSize.y()});
    SetSize({worldSize.x(), borderWith});
}

void BottomBorder::CheckCollision(Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

void BottomBorder::CheckCollision(Game::Enemy * /*inCollider*/)
{
}
} // namespace Game