#include "GameSystem/BaseAppState.h"

namespace GameSystem
{
auto BaseAppState::IsExclusiveUpdate() -> bool
{
    return false;
}
auto BaseAppState::IsExclusiveDraw() -> bool
{
    return false;
}
} // namespace GameSystem
