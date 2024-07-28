#pragma once
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"

namespace GameBase
{

class Collider
{
  public:
    virtual void CheckCollision(Collider *inCollider);
    auto GetRectangle() -> const Box2D &;

  protected:
    Box2D rectangle;
};

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public Collider
{
  public:
    Entity(const Box2D &inRectangle, const double &inMaxSpeed);

    virtual void CheckCollision(Collider *inCollider) override {};
    virtual void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

    virtual void Update(const double deltaTime) override;
    virtual void SetDirection(const Vector2D &inSpeed);
    virtual void SetEnginePower(const double &inPowerPercent);

    void SetWaitForDelete();
    auto IsWaitingForDelete() const -> bool;

  private:
    bool waitingForDelete;

    Vector2D direction;
    double maxSpeed;
    double powerPercent;
};

}; // namespace GameBase