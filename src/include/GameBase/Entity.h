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
    explicit Collider(const Box2D &inRectangle) : rectangle(inRectangle) {};
    virtual ~Collider() = default;

    virtual void CheckCollision(Collider *inCollider);
    auto GetRectangle() -> const Box2D &;

  protected:
    Box2D rectangle; // NOLINT
};

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public Collider
{
  public:
    Entity(const Box2D &inRectangle, const double &inMaxSpeed,
           const std::shared_ptr<BaseController> &inController);
    virtual ~Entity() = default;

    virtual void CheckCollision(Collider *inCollider) override {};
    virtual void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    virtual void Update(double deltaTime) override;
    virtual void SetDirection(const Vector2D &inSpeed);
    virtual void SetEnginePower(const double &inPowerPercent);

    void SetWaitForDelete();
    auto IsWaitingForDelete() const -> bool;

  private:
    bool waitingForDelete;

    Vector2D direction;
    double maxSpeed;
    double powerPercent;

    std::shared_ptr<BaseController> controller;
};

}; // namespace GameBase