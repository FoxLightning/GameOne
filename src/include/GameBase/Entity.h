#pragma once
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace GameBase
{

class Collider
{
  public:
    Collider() = default;
    virtual ~Collider() = default;

    virtual void CheckCollision(Collider *inCollider);
    [[nodiscard]] auto GetRectangle() const -> const Box2D &;

  protected:
    void SetRectangle(const Box2D &inRectangle);

  private:
    Box2D rectangle = Box2D(Vector2D(0., 0.), Vector2D(0., 0.));
};

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public Collider
{
  public:
    Entity() = default;
    ~Entity() override = default;

    void CheckCollision(Collider *inCollider) override {};
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override;

    virtual void SetDirection(const Vector2D &inSpeed);
    virtual void SetEnginePower(const double &inPowerPercent);
    virtual void SetMaxSpeed(const double &inMaxSpeed);

    void SetWaitForDelete();

    [[nodiscard]] auto GetPosition() const -> Vector2D;
    [[nodiscard]] auto IsWaitingForDelete() const -> bool;

  protected:
    auto GetController() -> std::shared_ptr<BaseController>;
    void SetController(const std::shared_ptr<BaseController> &inController);

  private:
    bool waitingForDelete = false;

    Vector2D direction = Vector2D(0., 0.);
    double maxSpeed = 0.;
    double powerPercent = 0.;

    std::shared_ptr<BaseController> controller;
};

}; // namespace GameBase