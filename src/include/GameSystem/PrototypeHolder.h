#pragma once
#include <map>
#include <memory>

namespace Game
{
class Enemy;
class Bullet;
} // namespace Game

namespace GameSystem
{
class BaseAnimation;
class Image;

class PrototypeHolder
{
  public:
    auto GetEnemy(const std::string &configName) -> std::shared_ptr<Game::Enemy>;
    auto GetBullet(const std::string &configName) -> std::shared_ptr<Game::Bullet>;
    auto GetImage(const std::string &configName) -> std::shared_ptr<Image>;
    auto GetAnimation(const std::string &configName) -> std::shared_ptr<BaseAnimation>;

  private:
    std::map<std::string, std::shared_ptr<Image>> imagePrototypes;
    std::map<std::string, std::shared_ptr<BaseAnimation>> animationPrototypes;
    std::map<std::string, std::shared_ptr<Game::Enemy>> enemyPrototypes;
    std::map<std::string, std::shared_ptr<Game::Bullet>> bulletPrototypes;
};

} // namespace GameSystem