#include "Game/Explosion.h"
#include "GameBase/Entity.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Collider.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include <cassert>
#include <memory>

namespace Game
{
Explosion::Explosion(Vector2D position, Vector2D direction, double speed, const char *animationName)
{
    SetPosition(position);
    SetMaxSpeed(speed);
    SetDirection(direction);
    PlayAnimation(animationName);
    const std::shared_ptr<GameSystem::BaseAnimation> &currentAnimation = GetCurrentAnimation();
    currentAnimation->BindOnAnimationFinished([this]() { SetWaitForDelete(); });
}

void Explosion::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    auto currentAnimation = GetCurrentAnimation();
    assert(currentAnimation);
    currentAnimation->Draw(inRenderer);
}

void Explosion::CheckCollision(GameSystem::Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

} // namespace Game