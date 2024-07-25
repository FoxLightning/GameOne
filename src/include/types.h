#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <cstdint>

typedef boost::geometry::model::d2::point_xy<double> Vector2D;
typedef boost::geometry::model::d2::point_xy<float> Vector2F;
typedef boost::geometry::model::d2::point_xy<int32_t> Vector2I;
typedef boost::geometry::model::d2::point_xy<int64_t> Vector2L;
