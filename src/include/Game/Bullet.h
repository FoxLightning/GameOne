#pragma once
#include "Constants.h"
#include "GameBase/Entity.h"

namespace Game
{

class Bullet final : public GameBase::Entity
{
  public:
    Bullet(const Vector2D &start, const Vector2D &direction);
    ~Bullet() override = default;
    void Update(double deltaTime) override;
    void Draw(std::shared_ptr<GameSystem::Renderer> inRenderer) override;
    [[nodiscard]] auto GetDamage() const -> double;

    void CheckCollision(GameBase::Collider *inCollider) override;
    void CheckCollision(Enemy *inCollider) override;

  private:
    double lifeTime = Const::System::bulletLifeTime;
    double bulletDamage = Const::Gameplay::bulletDamage;
};

}; // namespace Game