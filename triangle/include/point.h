#pragma once

#include "geometry.h"

namespace geometry {

struct point_t {
  double x_;
  double y_;
  double z_;

  point_t() : x_(0), y_(0), z_(0) {}
  point_t(const point_t& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}
  point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  point_t operator+(const point_t& p) const;
  point_t operator-(const point_t& p) const;
  bool operator==(const point_t& p) const;
  bool operator!=(const point_t& p) const;
  point_t operator=(const point_t& p);
  point_t operator*(double) const;

  bool is_intersect_points(const point_t& p) const;
};
} // geometry