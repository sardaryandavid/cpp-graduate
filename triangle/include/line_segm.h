#pragma once

#include "vector.h"

namespace geometry {

struct line_segm_t {
  point_t a_;
  point_t b_;

  line_segm_t(const point_t& a, const point_t& b) : a_(a), b_(b) {}
  bool is_intersect_line_segm(const line_segm_t& ls) const;
  bool is_intersect_point(const point_t& p) const;
};
} // geometry