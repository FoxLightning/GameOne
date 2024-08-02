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
    auto GetRectangle() -> const Box2D &;

  protected:
    void SetRectangle(const Box2D &inRectangle);

  private:
    Box2D rectangle;
};

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public Collider
{
  public:
    Entity();
    virtual ~Entity() = default;

    void CheckCollision(Collider *inCollider) override {};
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    void Update(double deltaTime) override;

    virtual void SetDirection(const Vector2D &inSpeed);
    virtual void SetEnginePower(const double &inPowerPercent);
    virtual void SetMaxSpeed(const double &inMaxSpeed);

    void SetWaitForDelete();
    auto IsWaitingForDelete() const -> bool;

  protected:
    auto GetController() -> std::shared_ptr<BaseController>;
    void SetController(const std::shared_ptr<BaseController> &inController);

  private:
    bool waitingForDelete;

    Vector2D direction;
    double maxSpeed;
    double powerPercent;

    std::shared_ptr<BaseController> controller;
};

}; // namespace GameBase