#include "plane.h"

namespace geometry {
bool plane_t::plane_intersection(const plane_t& p, line_t& l) const {
  vector_t d = n_.vector_mult(p.n_);
  if (is_eq(d.len(), 0))
    return false;

  double s1 = -d_;
  double s2 = -p.d_;
  double n1n2 = n_.scalar_mult(p.n_);
  double n1_norm = n_.scalar_mult(n_);
  double n2_norm = p.n_.scalar_mult(p.n_);

  double a = (s2 * n1n2 - s1 * n2_norm) / (n1n2 * n1n2 - n1_norm * n2_norm);
  double b = (s1 * n1n2 - s2 * n2_norm) / (n1n2 * n1n2 - n1_norm * n2_norm);
  l.p_ = n_ * a + p.n_ * b;
  l.d_ = n_.vector_mult(p.n_);

  return true;
}

double plane_t::signed_distance_to_point(const vector_t& p) const {
  double r = n_.scalar_mult(p) + d_;
  return r;
}

void plane_t::print() const { n_.print(); std::cout << d_ << std::endl; }
} // geometry