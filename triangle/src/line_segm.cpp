#include "line_segm.h"

namespace geometry {

/* Algorithm: 
 * math.stackexchange.com/questions/3114665/how-to-find-if-two-line-segments-intersect-in-3d */
bool line_segm_t::is_intersect(const line_segm_t& ls) const {
  double a1 = a_.x_ - b_.x_;
  double a2 = ls.b_.x_ - ls.a_.x_;
  double a3 = ls.b_.x_ - b_.x_;
  double b1 = a_.y_ - b_.y_;
  double b2 = ls.b_.y_ - ls.a_.y_;
  double b3 = ls.b_.y_ - b_.y_;
  double t, s;

  if (!solve_system(a1, a2, a3, b1, b2, b3, t, s))
    return false;
  
  double c1 = a_.z_ - b_.z_;
  double c2 = ls.b_.z_ - ls.a_.z_;
  double c3 = ls.b_.z_ - b_.z_;

  if (t >= 0 && t <= 1 && 
      s >= 0 && s <= 1 && 
      is_eq(t * c1 + s * c2, c3))
    return true;
  
  return false;
}
} // geometry