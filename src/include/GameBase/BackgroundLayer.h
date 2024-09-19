#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "GameSystem/Renderer.h"
#include <memory>

namespace GameBase
{
class BackgroundLayer : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    explicit BackgroundLayer(double inSpeed, const Vector2D &inSize,
                             std::vector<std::shared_ptr<GameSystem::Image>> inImages);

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    auto ShouldGenerateNewImage() -> bool;

    std::shared_ptr<GameSystem::Image> curImage;
    std::shared_ptr<GameSystem::Image> nextImage;
    std::vector<std::shared_ptr<GameSystem::Image>> imageList;

    Vector2D worldSize{0., 0.};
    uint32_t currentIndex = 0;
    double speed = 0;
    double currentPosition = 0;
};
} // namespace GameBase