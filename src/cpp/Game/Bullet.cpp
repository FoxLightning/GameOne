#include "Game/Bullet.h"
#include "Constants.h"
#include "Game/Enemy.h"
#include "Game/Explosion.h"
#include "GameBase/Entity.h"
#include "GameBase/GameState.h"
#include "GameBase/GameWorld.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Collider.h"
#include "GameSystem/PrototypeHolder.h"
#include "Types.h"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree_fwd.hpp"
#include <memory>
#include <string>
#include <utility>

namespace Game
{

Bullet::Bullet(std::string inConfigName) : configName(std::move(inConfigName))
{
    boost::property_tree::ptree bulletAssetTree;
    boost::property_tree::read_json(configName, bulletAssetTree);

    SetSize({bulletAssetTree.get_child("collider").get_child("size").get<double>("x"),
             bulletAssetTree.get_child("collider").get_child("size").get<double>("y")});
    SetPivot({bulletAssetTree.get_child("collider").get_child("pivot").get<double>("x"),
              bulletAssetTree.get_child("collider").get_child("pivot").get<double>("y")});
    SetDirection(Vector2D(0., -1.));
    SetMaxSpeed(bulletAssetTree.get<double>("speed"));
    bulletDamage = bulletAssetTree.get<double>("damage");
    const std::shared_ptr<GameSystem::PrototypeHolder> prototypeHolder = GameSystem::AppInstance::GetPrototypeHolder();
    SetImage(prototypeHolder->GetImage(bulletAssetTree.get<std::string>("image")));
}

void Bullet::Update(double deltaTime)
{
    lifeTime -= deltaTime;
    if (lifeTime < 0.)
    {
        SetWaitForDelete();
    }
    GameBase::Entity::Update(deltaTime);
}

auto Bullet::GetDamage() const -> double
{
    return bulletDamage;
}

void Bullet::CheckCollision(GameSystem::Collider *inCollider)
{
    inCollider->CheckCollision(this);
}

void Bullet::CheckCollision(Enemy * /*inCollider*/)
{
    const std::shared_ptr<GameBase::GameState> &currentGameState = GameSystem::AppInstance::GetCurrentAppState();
    currentGameState->GetGameWorld()->AddEntity<Game::Explosion>(GetPosition(), Vector2D(0., 0.), 0.,
                                                                 Const::Prototype::Animation::missleExplosionAnimation);
    SetWaitForDelete();
}

}; // namespace Game
