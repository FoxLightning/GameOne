#include "GameBase/GameWorld.h"
#include "GameBase/Entity.h"
#include "GameSystem/Renderer.h"
#include "boost/geometry/algorithms/detail/intersects/interface.hpp"
#include <algorithm>
#include <memory>

namespace GameBase
{

void GameWorld::Update(const double deltaTime)
{
    RemoveStaleObjects();
    CheckCollisions();
    UpdateChildren(deltaTime);
    AddPendingObjects();
}

void GameWorld::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    for (auto &entity : entitiesHolder)
    {
        entity->Draw(inRenderer);
    }
}

void GameWorld::CheckCollisions()
{
    for (auto &left : entitiesHolder)
    {
        for (auto &right : entitiesHolder)
        {
            if (CheckIntersections(left, right))
            {
                left->CheckCollision(right.get());
            }
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

void GameWorld::RemoveStaleObjects()
{
    auto range = std::ranges::remove_if(entitiesHolder, [](const auto &A) -> bool {
        if (A)
        {
            return A->IsWaitingForDelete();
        }
        return true;
    });
    entitiesHolder.erase(range.begin(), range.end());
}

auto GameWorld::CheckIntersections(const std::shared_ptr<Entity> &left, const std::shared_ptr<Entity> &right) -> bool
{
    if (left && right && left.get() != right.get())
    {
        return boost::geometry::intersects(left->GetRectangle(), right->GetRectangle());
    }
    return false;
}

void GameWorld::AddPendingObjects()
{
    entitiesHolder.insert(entitiesHolder.end(), entitiesToAdd.begin(), entitiesToAdd.end());
    entitiesToAdd.clear();
}

} // namespace GameBase