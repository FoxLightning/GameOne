#include "GameSystem/EventManager.h"
#include "GameSystem/InputManager.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace GameSystem
{
std::vector<InputActionDelegate> EventManager::inputActionSubscribers;
std::vector<EnemyDeathDelegate> EventManager::enemyDeathSubscribers;
std::vector<PlayerShipIntegrityDelegate> EventManager::playerShipIntegritySubscribers;

void EventManager::SubscribeInput(const InputActionDelegate &delegate)
{
    inputActionSubscribers.push_back(delegate);
}

void EventManager::UnsubscribeInput(const std::weak_ptr<void> &invoker)
{
    auto range = std::ranges::remove_if(
        inputActionSubscribers, [invoker](const auto &A) -> bool { return A.invoker.lock() == invoker.lock(); });
    inputActionSubscribers.erase(range.begin(), range.end());
}

void EventManager::BroadcastInput(EventType eventyType, ActionType actionType, InputContext currentContext)
{
    for (const auto &subscriber : inputActionSubscribers)
    {
        if (currentContext != subscriber.inputContext)
        {
            continue;
        }
        if (auto _ = subscriber.invoker.lock())
        {
            subscriber.callback(eventyType, actionType);
        }
    }
}

void EventManager::SubscribeEnemyDeath(const EnemyDeathDelegate &delegate)
{
    enemyDeathSubscribers.push_back(delegate);
}

void EventManager::UnsubscribeEnemyDeath(const std::weak_ptr<void> &invoker)
{
    auto range = std::ranges::remove_if(
        enemyDeathSubscribers, [invoker](const auto &A) -> bool { return A.invoker.lock() == invoker.lock(); });
    enemyDeathSubscribers.erase(range.begin(), range.end());
}

void EventManager::BroadcastEnemyDeath(uint64_t reward)
{
    for (const auto &subscriber : enemyDeathSubscribers)
    {
        if (auto _ = subscriber.invoker.lock())
        {
            subscriber.callback(reward);
        }
    }
}

void EventManager::SubscribePlayerShipIntegrityChange(const PlayerShipIntegrityDelegate &delegate)
{
    playerShipIntegritySubscribers.push_back(delegate);
}

void EventManager::UnsubscribePlayerShipIntegrityChange(const std::weak_ptr<void> &invoker)
{
    auto range = std::ranges::remove_if(playerShipIntegritySubscribers, [invoker](const auto &A) -> bool {
        return A.invoker.lock() == invoker.lock();
    });
    playerShipIntegritySubscribers.erase(range.begin(), range.end());
}

void EventManager::BroadcastPlayerShipIntegrityChange(uint64_t currentIntegrity)
{
    for (const auto &subscriber : playerShipIntegritySubscribers)
    {
        if (auto _ = subscriber.invoker.lock())
        {
            subscriber.callback(currentIntegrity);
        }
    }
}

} // namespace GameSystem