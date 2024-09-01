#include "GameBase/GameWorld.h"
#include "Constants.h"
#include "Game/BottomBorder.h"
#include "Game/SideBorder.h"
#include "GameBase/Background.h"
#include "GameBase/Entity.h"
#include "GameBase/Scenario.h"
#include "GameSystem/Renderer.h"
#include "boost/geometry/algorithms/detail/intersects/interface.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <algorithm>
#include <cassert>
#include <memory>

namespace GameBase
{

GameWorld::GameWorld()
{
    boost::property_tree::ptree worldAssetTree;
    boost::property_tree::read_json(Const::AssetPaths::gameWorld, worldAssetTree);
    worldSize = Vector2D{worldAssetTree.get<double>("worldSize.x"), worldAssetTree.get<double>("worldSize.y")};
    worldScreenOffset =
        Vector2D{worldAssetTree.get<double>("worldScreenOffset.x"), worldAssetTree.get<double>("worldScreenOffset.y")};
    assert(worldSize.x() > worldSize.y());
    currentScenario = std::make_shared<Scenario>(worldSize);
    for (const auto &side : {Game::SideBorder::Side::left, Game::SideBorder::Side::right, Game::SideBorder::Side::top})
    {
        AddEntity<Game::SideBorder>(worldSize, side);
    }
    AddEntity<Game::BottomBorder>(worldSize);
    background = std::make_shared<Background>(Const::Prototype::World::background, worldSize);
}

void GameWorld::Update(const double deltaTime)
{
    background->Update(deltaTime);
    currentScenario->Update(deltaTime);
    RemoveStaleObjects();
    AddPendingObjects();
    CheckCollisions();
    ApplyDesiredRectangles();
    UpdateChildren(deltaTime);
}

void GameWorld::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    inRenderer->SetViewPosition(worldScreenOffset);
    background->Draw(inRenderer);
    for (auto &entity : entitiesHolder)
    {
        assert(entity);
        entity->Draw(inRenderer);
    }
    inRenderer->PopViewPosition();
}

void GameWorld::AddEntity(const std::shared_ptr<Entity> &inEntity)
{
    entitiesToAdd.push_back(inEntity);
}

auto GameWorld::GetWorldSize() -> Vector2D
{
    return worldSize;
}

void GameWorld::ApplyDesiredRectangles()
{
    for (auto &child : entitiesHolder)
    {
        child->ApplyDesiredPosition();
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
        return boost::geometry::intersects(left->GetDesiredRectangle(), right->GetDesiredRectangle());
    }
    return false;
}

void GameWorld::AddPendingObjects()
{
    entitiesHolder.insert(entitiesHolder.end(), entitiesToAdd.begin(), entitiesToAdd.end());
    entitiesToAdd.clear();
}

} // namespace GameBase