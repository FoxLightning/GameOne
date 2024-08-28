#pragma once
#include "SDL3/SDL_rect.h"
#include "boost/geometry.hpp" // NOLINT
#include <cstdint>

namespace bg = boost::geometry;
namespace bgm = bg::model;

using Vector2D = bgm::d2::point_xy<double>;
using Vector2F = bgm::d2::point_xy<float>;
using Vector2I = bgm::d2::point_xy<int32_t>;
using Vector2L = bgm::d2::point_xy<int64_t>;
using Box2D = bgm::box<bgm::d2::point_xy<double>>;

template <typename T>
auto operator+(const bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(left.x() + right.x(), left.y() + right.y());
}

template <typename T>
auto operator-(const bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(left.x() - right.x(), left.y() - right.y());
}

template <typename T>
auto operator+=(bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right) -> bgm::d2::point_xy<T>
{
    left.x(left.x() + right.x());
    left.y(left.y() + right.y());
    return left;
}

template <typename T>
auto operator-=(bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right) -> bgm::d2::point_xy<T>
{
    left.x(left.x() - right.x());
    left.y(left.y() - right.y());
    return left;
}

template <typename T>
auto operator*(const bgm::d2::point_xy<T> &point, T scalar) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(point.x() * scalar, point.y() * scalar);
}

template <typename T>
auto operator*(T scalar, const bgm::d2::point_xy<T> &point) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(point.x() * scalar, point.y() * scalar);
}

template <typename T>
auto operator/(const bgm::d2::point_xy<T> &point, T scalar) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(point.x() / scalar, point.y() / scalar);
}

template <typename T>
auto operator/(T scalar, const bgm::d2::point_xy<T> &point) -> bgm::d2::point_xy<T>
{
    return bgm::d2::point_xy<T>(point.x() / scalar, point.y() / scalar);
}

template <typename T>
auto Normalize(const T &point) -> T
{
    auto dst = bg::distance(Vector2D(), point);
    if (dst > 0)
    {
        return point / dst;
    }
    return point;
}

template <typename T>
auto MoveBox(const bgm::box<bgm::d2::point_xy<T>> &box,
             const bgm::d2::point_xy<T> &point) -> bgm::box<bgm::d2::point_xy<T>>
{
    const bgm::d2::point_xy<T> min_corner(box.min_corner() + point);

    const bgm::d2::point_xy<T> max_corner(box.max_corner() + point);
    return bgm::box<bgm::d2::point_xy<T>>(min_corner, max_corner);
}

template <typename T>
auto ScaleBox(const bgm::box<bgm::d2::point_xy<T>> &box, const T &scale) -> bgm::box<bgm::d2::point_xy<T>>
{
    const bgm::d2::point_xy<T> min_corner(box.min_corner() * scale);
    const bgm::d2::point_xy<T> max_corner(box.max_corner() * scale);
    return bgm::box<bgm::d2::point_xy<T>>(min_corner, max_corner);
}

template <typename T>
auto operator*(const bgm::box<bgm::d2::point_xy<T>> &box, const T &scale) -> bgm::box<bgm::d2::point_xy<T>>
{
    return ScaleBox(box, scale);
}

template <typename T>
auto operator-(const bgm::box<bgm::d2::point_xy<T>> &box,
               const bgm::d2::point_xy<T> &point) -> bgm::box<bgm::d2::point_xy<T>>
{
    return MoveBox(box, point * (static_cast<T>(-1)));
}

template <typename T>
auto operator+(const bgm::box<bgm::d2::point_xy<T>> &box,
               const bgm::d2::point_xy<T> &point) -> bgm::box<bgm::d2::point_xy<T>>
{
    return MoveBox(box, point);
}

template <typename T>
auto operator+=(bgm::box<bgm::d2::point_xy<T>> &box,
                const bgm::d2::point_xy<T> &point) -> bgm::box<bgm::d2::point_xy<T>>
{
    return box = MoveBox(box, point);
}

template <typename T>
auto CastSDL_FRect(const bgm::box<bgm::d2::point_xy<T>> &box) -> SDL_FRect
{
    return SDL_FRect{static_cast<float>(box.min_corner().x()), static_cast<float>(box.min_corner().y()),
                     static_cast<float>(box.max_corner().x() - box.min_corner().x()),
                     static_cast<float>(box.max_corner().y() - box.min_corner().y())};
}

struct LinearColor
{
    uint8_t r = 0x00;
    uint8_t g = 0x00;
    uint8_t b = 0x00;
    uint8_t a = 0x00;
};
