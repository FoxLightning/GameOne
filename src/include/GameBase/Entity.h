#pragma once
#include "Constants.h"
#include "GameBase/BaseController.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <memory>

namespace Game
{
class Bullet;
class Enemy;
} // namespace Game

namespace GameBase
{

class Collider
{
  public:
    Collider() = default;
    virtual ~Collider() = default;

    virtual void CheckCollision(Collider *inCollider) = 0;
    virtual void CheckCollision(Game::Bullet *inCollider) {};
    virtual void CheckCollision(Game::Enemy *inCollider) {};
    virtual void CheckCollision(Game::PlayerShip *inCollider) {};
    [[nodiscard]] auto GetRectangle() const -> const Box2D &;

  protected:
    void SetSize(Vector2D inSize);
    void SetPosition(Vector2D inPosition);
    void SetPivot(Vector2D inPivot, bool updateRectangle = false);
    void Move(Vector2D delta);

  private:
    Vector2D pivot = Vector2D(0.5, 0.5);
    Box2D rectangle = Box2D(Vector2D(0., 0.), Vector2D(0., 0.));
};

class Entity : public GameSystem::IUpdateble, public GameSystem::IRendereble, public Collider
{
  public:
    Entity() = default;
    ~Entity() override = default;

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
    double powerPercent = 1.;

    std::shared_ptr<BaseController> controller;
};

}; // namespace GameBase