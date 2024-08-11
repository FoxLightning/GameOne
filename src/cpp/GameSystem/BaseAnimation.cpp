#include "GameSystem/BaseAnimation.h"
#include "Types.h"
#include "SDL3/SDL_render.h"
#include <cassert>
#include <cstdint>
#include <functional>
#include <utility>

namespace GameSystem
{

BaseAnimation::BaseAnimation(double inFrameTime, int64_t inFrameAmount, Vector2D tileSize, Vector2L tiles,
                             const Box2D *shape, SDL_Texture *texture)
    : frameTime(inFrameTime), frameAmount(inFrameAmount),
      renderAnimation({.currentFrame = 0, .tileSize = tileSize, .tiles = tiles, .shape = shape, .texture = texture})
{
}

void BaseAnimation::Update(double deltaTime)
{
    assert(!isFinished);
    if (renderAnimation.currentFrame >= frameAmount)
    {
        if (onAnimationFinished)
        {
            onAnimationFinished();
        }
        isFinished = true;
        return;
    }
    currentTime += deltaTime;
    renderAnimation.currentFrame = static_cast<int64_t>(currentTime / frameTime);
}

auto BaseAnimation::IsAnimationFinished() const -> bool
{
    return isFinished;
}

void BaseAnimation::BindOnAnimationFinished(std::function<void()> callback)
{
    onAnimationFinished = std::move(callback);
}

[[nodiscard]] auto BaseAnimation::GetRender() const -> const RenderAnimation &
{
    return renderAnimation;
}
} // namespace GameSystem