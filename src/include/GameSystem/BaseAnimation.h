#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <cstdint>

namespace GameSystem
{
class Texture;

class BaseAnimation : public IUpdateble, public IRendereble
{
  public:
    BaseAnimation(const BaseAnimation &other) = default;
    explicit BaseAnimation(const std::string &name);

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<Renderer> inRenderer) override;
    void SetPosition(const Vector2D &inPos);

    void BindOnAnimationFinished(std::function<void()> callback);
    [[nodiscard]] auto IsAnimationFinished() const -> bool;

  private:
    bool isFinished = false;
    double currentTime = 0;
    std::function<void()> onAnimationFinished;

    std::shared_ptr<Texture> atlas;
    Vector2D tileSize{0., 0.};
    Vector2I tiles{0, 0};
    int64_t frames{0};
    double frameTime{0.};
    Vector2D pos{0., 0.};
    Vector2D size{0., 0.};
    Vector2D pivot{0.5, 0.5};
};

} // namespace GameSystem
