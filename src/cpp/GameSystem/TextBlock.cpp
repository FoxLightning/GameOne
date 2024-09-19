#include "GameSystem/TextBlock.h"
#include "GameSystem/AppInstance.h"
#include "GameSystem/Image.h"
#include "GameSystem/ResurceManager.h"
#include "GameSystem/Texture.h"
#include "Types.h"
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

namespace GameSystem
{
TextBlock::TextBlock(std::string inText, const std::string &fontName, int32_t size, const LinearColor &inColor,
                     const Vector2D &inPos, const Vector2D &inPivot)
    : text(std::move(inText)), color(inColor), pos(inPos), pivot(inPivot)
{
    font = AppInstance::GetResurceManager()->GetFont(fontName, size);
    GenerateTextImage(text);
}

void TextBlock::SetText(const std::string &inText)
{
    if (text != inText)
    {
        GenerateTextImage(inText);
        text = inText;
    }
}

void TextBlock::SetColor(LinearColor inColor)
{
    color = inColor;
    GenerateTextImage(text);
}

void TextBlock::Draw(std::shared_ptr<Renderer> inRenderer)
{
    if (textImage)
    {
        textImage->Draw(inRenderer);
    }
}

void TextBlock::GenerateTextImage(const std::string &inText)
{
    const std::shared_ptr<Texture> texture = std::make_shared<Texture>(font, inText, color);
    textImage = std::make_shared<Image>(texture, texture->GetSize(), pivot);
    textImage->SetPos(pos);
}

} // namespace GameSystem