#include "line.h"

namespace geometry{

bool line_t::is_intersect_point_line(const point_t& p, const point_t& min, const point_t& max) const {
  if (p_ == p)
    return true;

  vector_t v = p_ - p;
  vector_t vp = p;

  return (v.is_collinear(d_) && vp.inside(min, max));
}
} // geometry