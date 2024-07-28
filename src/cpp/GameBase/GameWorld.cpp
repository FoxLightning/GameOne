#include "GameBase/GameWorld.h"
#include "GameBase/Entity.h"
#include "Types.h"
#include <memory>

namespace GameBase
{

GameWorld::GameWorld()
{
}

void GameWorld::Update(const double deltaTime)
{
    CheckCollisions();
    UpdateChildren(deltaTime);
}

void GameWorld::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    for (auto entity : entitiesHolder)
    {
        entity->Draw(inRenderer);
    }
}

void GameWorld::CheckCollisions()
{
    for (auto leftEntity : entitiesHolder)
    {
        auto *leftCollider = dynamic_cast<Collider *>(leftEntity.get());
        if (!leftCollider)
        {
            continue;
        }
        for (auto rightEntity : entitiesHolder)
        {
            auto *rightCollider = dynamic_cast<Collider *>(rightEntity.get());
            if (!rightCollider)
            {
                continue;
            }
            leftCollider->CheckCollision(rightCollider);
        }
    }
}

void GameWorld::UpdateChildren(const double deltaTime)
{
    for (auto &child : entitiesHolder)
    {
        child->Update(deltaTime);
    }
}

} // namespace GameBase