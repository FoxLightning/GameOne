#pragma once
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Image.h"
#include <memory>

namespace GameSystem
{
class PrototypeHolder
{
  public:
    PrototypeHolder();
    ~PrototypeHolder() = default;

    [[nodiscard]] auto GetImage(const std::string &name) -> std::shared_ptr<Image>;
    [[nodiscard]] auto GetAnimation(const std::string &name) -> std::shared_ptr<BaseAnimation>;

  private:
    std::map<std::string, std::shared_ptr<Image>> imagePrototypes;
    std::map<std::string, std::shared_ptr<BaseAnimation>> animationPrototypes;
};

} // namespace GameSystem