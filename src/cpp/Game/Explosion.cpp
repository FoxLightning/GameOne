#include "Game/Explosion.h"
#include "Constants.h"
#include "GameBase/Entity.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Renderer.h"
#include "Types.h"
#include "SDL3/SDL_render.h"
#include <cassert>
#include <cstdint>
#include <memory>

namespace Game
{
Explosion::Explosion(Vector2D position, Vector2D direction, double speed, double inFrameTime, int64_t inFrameAmount,
                     Vector2D tileSize, Vector2L tiles, SDL_Texture *texture)
{
    SetSize(Vector2D(Const::System::explosionSize, Const::System::explosionSize));
    SetPosition(position);
    SetMaxSpeed(speed);
    SetDirection(direction);
    PlayAnimation(std::make_shared<GameSystem::BaseAnimation>(inFrameTime, inFrameAmount, tileSize, tiles,
                                                              &GetRectangle(), texture));
    GetCurrentAnimation()->BindOnAnimationFinished([this]() { SetWaitForDelete(); });
}

void Explosion::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    auto currentAnimation = GetCurrentAnimation();
    assert(currentAnimation);
    inRenderer->Draw(currentAnimation->GetRender());
}

void Explosion::CheckCollision(GameBase::Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

} // namespace Game