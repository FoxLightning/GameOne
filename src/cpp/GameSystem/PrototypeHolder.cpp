#include "GameSystem/PrototypeHolder.h"
#include "Constants.h"
#include "GameSystem/Image.h"
#include <array>
#include <map>
#include <memory>
#include <string>

namespace GameSystem
{
PrototypeHolder::PrototypeHolder()
{
    const std::array<std::string, 3> imagesToLoad{Const::Prototypes::Image::enemy, Const::Prototypes::Image::ship,
                                                  Const::Prototypes::Image::missle};
    for (const auto &imageName : imagesToLoad)
    {
        imagePrototypes.emplace(imageName, std::make_shared<Image>(imageName));
    }
}

auto PrototypeHolder::GetImage(const std::string &name) -> std::shared_ptr<Image>
{
    return imagePrototypes[name];
}

} // namespace GameSystem