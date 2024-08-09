#pragma once
#include "GameSystem/AppInstance.h"
#include "Types.h"
#include "SDL3/SDL_render.h"
#include <cstdint>

namespace GameSystem
{

struct RenderAnimation
{
    int64_t currentFrame;
    Vector2D tileSize;
    Vector2L tiles;
    const Box2D *shape;
    SDL_Texture *texture;
};

class BaseAnimation : public IUpdateble
{
  public:
    BaseAnimation(double inFrameTime, int64_t inFrameAmount, Vector2D tileSize, Vector2L tiles, const Box2D *shape,
                  SDL_Texture *texture);

    void Update(double deltaTime) override;
    void BindOnAnimationFinished(std::function<void()> callback);
    [[nodiscard]] auto GetRender() const -> const RenderAnimation &;
    [[nodiscard]] auto IsAnimationFinished() const -> bool;

  private:
    bool isFinished = false;
    double currentTime = 0;

    double frameTime;
    int64_t frameAmount;

    std::function<void()> onAnimationFinished;
    RenderAnimation renderAnimation;
};

} // namespace GameSystem
