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
  double b = (s1 * n1n2 - s2 * n1_norm) / (n1n2 * n1n2 - n1_norm * n2_norm);
  l.p_ = n_ * a + p.n_ * b;
  l.d_ = d;

  return true;
}

double plane_t::signed_distance_to_point(const vector_t& p) const {
  double r = n_.scalar_mult(p) + d_;
  return r;
}

bool plane_t::is_coincident(const plane_t& p) const {
  double len1 = n_.len();
  double len2 = p.n_.len();

  double d1 = d_ / len1;
  double d2 = p.d_ / len2;

  if ((n_.is_collinear(p.n_)) &&
     ((is_pos(n_.scalar_mult(p.n_)) && is_eq(d1, d2)) ||
     (is_neg(n_.scalar_mult(p.n_)) && is_eq(d1, -d2))))
     return true;

  return false;
}

bool plane_t::is_parallel(const plane_t& p) const {
  vector_t v = n_.vector_mult(p.n_);
  return is_eq(v.len(), 0);
}

void plane_t::print() const { 
  n_.print(); std::cout << d_ << std::endl; 
}
} // geometry