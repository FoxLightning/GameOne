#pragma once
#include <exception>
#include <format>
#include <string>
#include <utility>

namespace GameSystem
{
class CriticalException : public std::exception
{
  public:
    explicit CriticalException(std::string inReason) : reason(std::move(inReason))
    {
    }

    [[nodiscard]] auto what() const noexcept -> const char * override
    {
        return reason.c_str();
    }

  private:
    std::string reason;
};

class InvalidDataException : public std::exception
{
  public:
    explicit InvalidDataException(std::string inReason, std::string inPath)
        : reason(std::format("Reason {}. Path '{}'.", inReason, inPath))
    {
    }

    [[nodiscard]] auto what() const noexcept -> const char * override
    {
        return reason.c_str();
    }

  private:
    std::string reason;
};
} // namespace GameSystem