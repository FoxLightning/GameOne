#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Collider.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace GameSystem
{
class BaseAnimation;
class Image;
} // namespace GameSystem

namespace GameBase
{
class BaseController;

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public GameSystem::Collider
{
  public:
    Entity() = default;
    ~Entity() override = default;
    Entity(const Entity &other);

    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override;

    virtual void SetDirection(const Vector2D &inSpeed);
    virtual void SetEnginePower(const double &inPowerPercent);
    virtual void SetMaxSpeed(const double &inMaxSpeed);

    void SetWaitForDelete();

    [[nodiscard]] auto IsWaitingForDelete() const -> bool;

  protected:
    auto GetController() -> std::shared_ptr<BaseController>;
    [[nodiscard]] auto GetCurrentAnimation() const -> const std::shared_ptr<GameSystem::BaseAnimation> &;
    [[nodiscard]] auto GetMaxSpeed() const -> double;
    [[nodiscard]] auto GetDirection() const -> Vector2D;

    void SetImage(const std::shared_ptr<GameSystem::Image> &inImage);
    void SetController(const std::shared_ptr<BaseController> &inController);
    void PlayAnimation(const char *animatiionName);

  private:
    std::shared_ptr<GameSystem::BaseAnimation> animation;
    bool waitingForDelete = false;

    Vector2D direction = Vector2D(0., 0.);
    double maxSpeed = 0.;
    double powerPercent = 1.;

    std::shared_ptr<BaseController> controller;
    std::shared_ptr<GameSystem::Image> image;
};

}; // namespace GameBase