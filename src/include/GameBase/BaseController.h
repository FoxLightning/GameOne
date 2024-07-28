#pragma once
#include "GameSystem/AppInstance.h"
#include <memory>

namespace GameBase
{
class Entity;

class BaseController : public GameSystem::IUpdateble
{
  public:
    BaseController(std::weak_ptr<Entity> inEntity);
    virtual void Update(const double deltaTime) override;

  private:
    std::weak_ptr<Entity> entity;
};

}; // namespace GameBase