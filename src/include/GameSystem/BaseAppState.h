#pragma once

#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"

namespace GameSystem
{
class BaseAppState : public IUpdateble, public IRendereble
{
  public:
    virtual auto IsExclusiveUpdate() -> bool;
    virtual auto IsExclusiveDraw() -> bool;
};
} // namespace GameSystem