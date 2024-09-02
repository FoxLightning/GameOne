#pragma once
#include <string>

struct TTF_Font;

namespace GameSystem
{
class Font final
{
  public:
    explicit Font(const std::string &inName, int32_t size);
    ~Font();
    auto Get() -> TTF_Font *;
    auto GetName() -> std::string;

  private:
    std::string name;
    TTF_Font *fontObject;
};

} // namespace GameSystem