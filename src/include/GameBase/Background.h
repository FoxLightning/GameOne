#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "GameSystem/Renderer.h"
#include <memory>
#include <string>

namespace GameSystem
{

}
namespace GameBase
{
class Background : GameSystem::IUpdateble, GameSystem::IRendereble
{
  public:
    explicit Background(const std::string &configName);

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    auto ShouldGenerateNewImage() -> bool;

    std::shared_ptr<GameSystem::Image> curImage;
    std::shared_ptr<GameSystem::Image> nextImage;
    std::vector<std::shared_ptr<GameSystem::Image>> imageList;

    uint32_t currentIndex = 0;
    double speed = 0;
    double currentPosition = 0;
};
} // namespace GameBase