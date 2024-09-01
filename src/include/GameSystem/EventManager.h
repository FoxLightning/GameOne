#pragma once
#include "GameSystem/InputManager.h"
#include <functional>
#include <memory>

namespace Game
{
class Enemy;
}

namespace GameSystem
{

struct InputActionDelegate
{
    std::weak_ptr<void> invoker;
    std::function<void(EventType, ActionType)> callback;
};

struct EnemyDeathDelegate
{
    std::weak_ptr<void> invoker;
    std::function<void(double reward)> callback;
};

class EventManager
{
  public:
    EventManager() = default;

    static void SubscribeInput(const InputActionDelegate &delegate);
    static void UnsubscribeInput(const std::weak_ptr<void> &invoker);
    static void BroadcastInput(EventType eventyType, ActionType actionType);

    static void SubscribeEnemyDeath(const EnemyDeathDelegate &delegate);
    static void UnsubscribeEnemyDeath(const std::weak_ptr<void> &invoker);
    static void BroadcastEnemyDeath(double reward);

  private:
    static std::vector<InputActionDelegate> inputActionSubscribers;
    static std::vector<EnemyDeathDelegate> enemyDeathSubscribers;
};

} // namespace GameSystem