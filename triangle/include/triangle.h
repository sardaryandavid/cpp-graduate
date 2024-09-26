#pragma once

#include <iostream>
#include "plane.h"
#include "line_segm.h"

namespace geometry {

enum fig {point = 0, line, triangle};
constexpr int triangle_vertices_num = 3;

struct triangle_t {
  point_t v1_;
  point_t v2_;
  point_t v3_;

  triangle_t(const point_t& v1, const point_t& v2, const point_t& v3) : v1_(v1), v2_(v2), v3_(v3) {}

  plane_t get_plane() const;

  /* Suppot functions for the method of separation axes */
  void compute_interval(const vector_t& d, double& min, double& max) const;

  bool check_d(const triangle_t& t, const vector_t& v1, const vector_t& v2, const plane_t& p) const;

  /* Implementation the method of separation axes */
  bool is_intersect_2d(const triangle_t& t) const;

  fig degenerate() const;

  /* WARNING: use only if triangle degenerates to line or line segment */
  line_t make_line() const;
  line_segm_t make_line_segm() const;

  bool is_intersect_triangles_3d(const triangle_t& t) const;
  bool check_corner_cases(const triangle_t& t, bool& is_corner_case) const;
  point_t min() const;
  point_t max() const;
  point_t min(const triangle_t& t) const;
  point_t max(const triangle_t& t) const;

  inline void print() const;
};
} // geometry