#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include <memory>
#include <string>

namespace GameBase
{
class BackgroundLayer;

class Background : public GameSystem::IUpdateble, public GameSystem::IRendereble
{
  public:
    explicit Background(const std::string &configName, const Vector2D &size);

    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    std::vector<std::shared_ptr<BackgroundLayer>> parallaxLayers;
};
} // namespace GameBase