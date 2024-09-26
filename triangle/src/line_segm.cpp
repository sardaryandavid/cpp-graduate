#include "line_segm.h"

namespace geometry {

static bool check_segm_equation(double a1, double a2, double a3, double t, double s) {
  return (t >= 0 && t <= 1 &&
          s >= 0 && s <= 1 &&
          is_eq(t * a1 + s * a2, a3));
}

static bool is_sol_exist(double a1, double a2, double a3) {
  if (is_eq(a1, 0)) {
    if (is_eq(a2, 0) && !is_eq(a3, 0))
      return false;

    return (((a3 / a2) >= 0) && ((a3 / a2) <= 1));
  }

  else if (is_eq(a2, 0)) {
    return is_eq(a3, 0);
  }

  double b1 = std::min(a3 / a1, (a3 - a2) / a1);
  double b2 = std::max(a3 / a1, (a3 - a2) / a1);

  if (is_neg(b2) || is_pos(b1 - 1))
    return false;

  return true;
}

static bool solve_system_and_check(double a1, double a2, double a3,
                                   double b1, double b2, double b3,
                                   double c1, double c2, double c3) {
  double t, s;
  bool is_inf_sols;
  if (solve_system(a1, a2, a3, b1, b2, b3, t, s, is_inf_sols)) {
    if (is_inf_sols)
      return is_sol_exist(c1 , c2, c3);

    return check_segm_equation(c1, c2, c3, t, s);
  }

  return false;
}

/* Algorithm: 
 * math.stackexchange.com/questions/3114665/how-to-find-if-two-line-segments-intersect-in-3d */
bool line_segm_t::is_intersect_line_segm(const line_segm_t& ls) const {
  double a1 = a_.x_ - b_.x_;
  double a2 = ls.b_.x_ - ls.a_.x_;
  double a3 = ls.b_.x_ - b_.x_;
  double b1 = a_.y_ - b_.y_;
  double b2 = ls.b_.y_ - ls.a_.y_;
  double b3 = ls.b_.y_ - b_.y_;
  double c1 = a_.z_ - b_.z_;
  double c2 = ls.b_.z_ - ls.a_.z_;
  double c3 = ls.b_.z_ - b_.z_;

  if (is_eq(det(a1, a2, b1, b2), 0)) {
    if (!is_eq(det(a1, a2, c1, c2), 0))
      return solve_system_and_check(a1, a2, a3, c1, c2, c3, b1, b2, b3);

    else
      return solve_system_and_check(c1, c2, c3, b1, b2, b3, a1, a2, a3); 
  }

  else
    return solve_system_and_check(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

bool line_segm_t::is_intersect_point(const point_t& p) const {
  if (a_ == p)
    return true;

  vector_t v1 = p - a_;
  vector_t v2 = b_ - a_;
  vector_t vp = p;
  return (v1.is_collinear(v2) && vp.inside(a_, b_));
}
} // geometry