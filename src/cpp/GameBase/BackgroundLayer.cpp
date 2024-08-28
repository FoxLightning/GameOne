#include "GameBase/BackgroundLayer.h"
#include "GameBase/Background.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "Types.h"
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace GameBase
{

void BackgroundLayer::Update(double deltaTime)
{
    curImage->SetPos({0, currentPosition});
    nextImage->SetPos({0, currentPosition - curImage->GetSize().y()});
    currentPosition += speed * deltaTime;

    if (ShouldGenerateNewImage())
    {
        currentIndex = (currentIndex + 1) % imageList.size();
        currentPosition = currentPosition - nextImage->GetSize().y();

        curImage = std::move(nextImage);
        nextImage = imageList[(currentIndex + 1) % imageList.size()];
    }
}

void BackgroundLayer::Draw(std::shared_ptr<GameSystem::Renderer> inRenderer)
{
    nextImage->Draw(inRenderer);
    curImage->Draw(inRenderer);
}

auto BackgroundLayer::ShouldGenerateNewImage() -> bool
{
    return currentPosition > curImage->GetSize().y();
}

BackgroundLayer::BackgroundLayer(const double inSpeed, const Vector2D &inSize,
                                 std::vector<std::shared_ptr<GameSystem::Image>> inImages)
    : worldSize(inSize), speed(inSpeed), imageList(std::move(inImages))
{
    assert(imageList.size() >= 2);
    curImage = imageList[0];
    nextImage = imageList[1];
}
} // namespace GameBase
