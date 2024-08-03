#pragma once

#include "GameBase/Entity.h"

namespace Game
{

class Bullet : public GameBase::Entity
{
  public:
    Bullet(const Vector2D &start, const Vector2D &direction);
    ~Bullet() override = default;
    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;

  private:
    double lifeTime = 10.;
};

}; // namespace Game