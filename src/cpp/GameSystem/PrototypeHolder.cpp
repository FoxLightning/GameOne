#include "GameSystem/PrototypeHolder.h"
#include "Constants.h"
#include "GameSystem/BaseAnimation.h"
#include "GameSystem/Image.h"
#include <array>
#include <cassert>
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

    const std::array<std::string, 3> animationsToLoad{Const::Prototypes::Animation::enemyDamageAnimation,
                                                      Const::Prototypes::Animation::enemyExplosionAnimation,
                                                      Const::Prototypes::Animation::missleExplosionAnimation};
    for (const auto &animationName : animationsToLoad)
    {
        animationPrototypes.emplace(animationName, std::make_shared<BaseAnimation>(animationName));
    }
}

auto PrototypeHolder::GetImage(const std::string &name) -> std::shared_ptr<Image>
{
    assert(imagePrototypes.contains(name));
    return std::make_shared<Image>(*imagePrototypes[name]);
}

auto PrototypeHolder::GetAnimation(const std::string &name) -> std::shared_ptr<BaseAnimation>
{
    assert(animationPrototypes.contains(name));
    return std::make_shared<BaseAnimation>(*animationPrototypes[name]);
}

} // namespace GameSystem