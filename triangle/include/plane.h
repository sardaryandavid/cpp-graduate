#pragma once 

#include <iostream>
#include "line.h"

namespace geometry {

struct plane_t {
  vector_t n_;
  double d_;

  plane_t(double a, double b, double c, double d) : n_(a, b, c), d_(d) {}
  plane_t(const vector_t& n, double d) : n_(n), d_(d) {}

  bool is_coincident(const plane_t&) const;
  bool is_parallel(const plane_t& p) const;
  bool plane_intersection(const plane_t& p, line_t& l) const;
  double signed_distance_to_point(const vector_t& p) const;

  void print() const;
};
} // geometry