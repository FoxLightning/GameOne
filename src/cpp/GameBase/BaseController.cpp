#include "GameBase/BaseController.h"
#include "GameBase/Entity.h"

namespace GameBase
{

BaseController::BaseController(std::weak_ptr<Entity> inEntity)
{
    entity = inEntity;
}

void BaseController::Update(const double deltaTime)
{
    if (auto entityShared = entity.lock())
    {
        entityShared->SetDirection(Vector2D{1.f, 0});
        entityShared->SetEnginePower(1.f);
    }
}

}; // namespace GameBase