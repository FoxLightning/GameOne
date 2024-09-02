#include "GameSystem/Font.h"
#include "GameSystem/Exceptions.h"
#include "SDL3/SDL_error.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstdint>
#include <format>
#include <string>

namespace GameSystem
{
Font::Font(const std::string &inName, const int32_t size) : name(inName), fontObject(TTF_OpenFont(inName.c_str(), size))
{
    if (!fontObject)
    {
        throw InvalidDataException(std::format("Unable to open font. SDL_Error: {}.", SDL_GetError()), inName);
    }
}

Font::~Font()
{
    TTF_CloseFont(fontObject);
}

auto Font::Get() -> TTF_Font *
{
    return fontObject;
}

auto Font::GetName() -> std::string
{
    return name;
}

} // namespace GameSystem
