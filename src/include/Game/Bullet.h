#pragma once
#include "Constants.h"
#include "GameBase/Entity.h"

namespace Game
{

class Bullet final : public GameBase::Entity
{
  public:
    explicit Bullet(std::string inConfigName);
    Bullet(const Bullet &other) = default;

    ~Bullet() override = default;
    void Update(double deltaTime) override;
    [[nodiscard]] auto GetDamage() const -> double;

    void CheckCollision(GameBase::Collider *inCollider) override;
    void CheckCollision(Enemy *inCollider) override;

  private:
    double lifeTime = Const::System::bulletLifeTime;
    double bulletDamage;

    std::string configName;
};

}; // namespace Game