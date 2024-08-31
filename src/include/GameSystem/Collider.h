#pragma once
#include "Types.h"

namespace Game
{
class Bullet;
class Enemy;
class Explosion;
class PlayerShip;
} // namespace Game

namespace GameSystem
{
class Collider
{
  public:
    Collider() = default;
    virtual ~Collider() = default;

    virtual void CheckCollision(Collider *inCollider) = 0;
    virtual void CheckCollision(Game::Bullet *inCollider) {};
    virtual void CheckCollision(Game::Enemy *inCollider) {};
    virtual void CheckCollision(Game::Explosion *inCollider) {};
    virtual void CheckCollision(Game::PlayerShip *inCollider) {};
    [[nodiscard]] auto GetRectangle() const -> const Box2D &;
    void SetPosition(Vector2D inPosition);

  protected:
    void SetSize(Vector2D inSize);
    void SetPivot(Vector2D inPivot, bool updateRectangle = false);
    void Move(Vector2D delta);

  private:
    Vector2D pivot = Vector2D(0.5, 0.5);
    Box2D rectangle = Box2D(Vector2D(0., 0.), Vector2D(0., 0.));
};
} // namespace GameSystem
