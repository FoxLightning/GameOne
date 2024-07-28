#pragma once

#include "boost/geometry.hpp"
#include "boost/geometry/geometries/point.hpp"
#include "SDL3/SDL.h"
#include <cstdint>

namespace bg = boost::geometry;
namespace bgm = bg::model;

typedef bgm::d2::point_xy<double> Vector2D;
typedef bgm::d2::point_xy<float> Vector2F;
typedef bgm::d2::point_xy<int32_t> Vector2I;
typedef bgm::d2::point_xy<int64_t> Vector2L;
typedef bgm::box<bgm::d2::point_xy<double>> Box2D;

#define AreIntersects bg::intersects
#define Distance bg::distance

template <typename T>
bgm::d2::point_xy<T> operator+(const bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right)
{
    return bgm::d2::point_xy<T>(left.x() + right.x(), left.y() + right.y());
}

template <typename T>
bgm::d2::point_xy<T> operator-(const bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right)
{
    return bgm::d2::point_xy<T>(left.x() - right.x(), left.y() - right.y());
}

template <typename T> bgm::d2::point_xy<T> operator+=(bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right)
{
    left.x(left.x() + right.x());
    left.y(left.y() + right.y());
    return left;
}

template <typename T> bgm::d2::point_xy<T> operator-=(bgm::d2::point_xy<T> &left, const bgm::d2::point_xy<T> &right)
{
    left.x(left.x() - right.x());
    left.y(left.y() - right.y());
    return left;
}

template <typename T> bgm::d2::point_xy<T> operator*(const bgm::d2::point_xy<T> &point, T scalar)
{
    return bgm::d2::point_xy<T>(point.x() * scalar, point.y() * scalar);
}

template <typename T> bgm::d2::point_xy<T> operator*(T scalar, const bgm::d2::point_xy<T> &point)
{
    return bgm::d2::point_xy<T>(point.x() * scalar, point.y() * scalar);
}

template <typename T> bgm::d2::point_xy<T> operator/(const bgm::d2::point_xy<T> &point, T scalar)
{
    return bgm::d2::point_xy<T>(point.x() / scalar, point.y() / scalar);
}

template <typename T> bgm::d2::point_xy<T> operator/(T scalar, const bgm::d2::point_xy<T> &point)
{
    return bgm::d2::point_xy<T>(point.x() / scalar, point.y() / scalar);
}

template <typename T> T Normalize(const T &point)
{
    auto dst = Distance(Vector2D(), point);
    if (dst > 0)
    {
        return point / dst;
    }
    return point;
}

template <typename T>
bgm::box<bgm::d2::point_xy<T>> MoveBox(const bgm::box<bgm::d2::point_xy<T>> &box, const bgm::d2::point_xy<T> &point)
{
    bgm::d2::point_xy<T> min_corner(box.min_corner() + point);

    bgm::d2::point_xy<T> max_corner(box.max_corner() + point);
    return bgm::box<bgm::d2::point_xy<T>>(min_corner, max_corner);
}

template <typename T>
bgm::box<bgm::d2::point_xy<T>> operator+=(bgm::box<bgm::d2::point_xy<T>> &box, const bgm::d2::point_xy<T> &point)
{
    return box = MoveBox(box, point);
}

template <typename T>
SDL_FRect CastSDL_FRect(const bgm::box<bgm::d2::point_xy<T>>& box)
{
    return SDL_FRect{
        static_cast<float>(box.min_corner().x()),
        static_cast<float>(box.min_corner().y()),
        static_cast<float>(box.max_corner().x() - box.min_corner().x()),
        static_cast<float>(box.max_corner().y() - box.min_corner().y())
    };
}
