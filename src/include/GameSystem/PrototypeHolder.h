#pragma once
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

  private:
    std::map<std::string, std::shared_ptr<Image>> imagePrototypes;
};

} // namespace GameSystem