#include "GameSystem/PrototypeHolder.h"
#include "Game/Bullet.h"
#include "Game/Enemy.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Image.h"
#include <cassert>
#include <map>
#include <memory>
#include <string>

namespace GameSystem
{
auto PrototypeHolder::GetEnemy(const std::string &configName) -> std::shared_ptr<Game::Enemy>
{
    if (auto enemyItr = enemyPrototypes.find(configName); enemyItr != enemyPrototypes.end())
    {
        return std::make_shared<Game::Enemy>(*(enemyItr->second));
    }
    enemyPrototypes.emplace(configName, std::make_shared<Game::Enemy>(configName));
    return std::make_shared<Game::Enemy>(*enemyPrototypes[configName]);
}

auto PrototypeHolder::GetBullet(const std::string &configName) -> std::shared_ptr<Game::Bullet>
{
    if (auto bulletItr = bulletPrototypes.find(configName); bulletItr != bulletPrototypes.end())
    {
        return std::make_shared<Game::Bullet>(*(bulletItr->second));
    }
    bulletPrototypes.emplace(configName, std::make_shared<Game::Bullet>(configName));
    return std::make_shared<Game::Bullet>(*bulletPrototypes[configName]);
}

auto PrototypeHolder::GetImage(const std::string &configName) -> std::shared_ptr<Image>
{
    if (auto imageItr = imagePrototypes.find(configName); imageItr != imagePrototypes.end())
    {
        return std::make_shared<Image>(*(imageItr->second));
    }
    imagePrototypes.emplace(configName, std::make_shared<Image>(configName));
    return std::make_shared<Image>(*imagePrototypes[configName].get());
}

auto PrototypeHolder::GetAnimation(const std::string &configName) -> std::shared_ptr<BaseAnimation>
{
    if (auto animationItr = animationPrototypes.find(configName); animationItr != animationPrototypes.end())
    {
        return std::make_shared<BaseAnimation>(*(animationItr->second));
    }
    animationPrototypes.emplace(configName, std::make_shared<BaseAnimation>(configName));
    return std::make_shared<BaseAnimation>(*animationPrototypes[configName]);
}

} // namespace GameSystem