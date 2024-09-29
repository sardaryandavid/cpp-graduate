#include <cassert>

#include "point.h"

namespace geometry {
  
point_t point_t::operator+(const point_t& p) const {
  point_t res{x_ + p.x_, y_ + p.y_, z_ + p.z_};
  return res;
}

point_t point_t::operator-(const point_t& p) const {
  point_t res{x_ - p.x_, y_ - p.y_, z_ - p.z_};
  return res;
}

bool point_t::operator==(const point_t& p) const {
  if(is_eq(x_, p.x_) && is_eq(y_, p.y_) && is_eq(z_, p.z_))
    return true;

  return false;
}

bool point_t::operator!=(const point_t& p) const {
  return !(*this == p);
}

point_t point_t::operator=(const point_t& p) {
  x_ = p.x_;
  y_ = p.y_;
  z_ = p.z_;

  return *this;
}

point_t point_t::operator*(double d) const {
  point_t res {x_ * d, y_ * d, z_ * d};
  return res;
}

bool point_t::is_intersect_point(const point_t& p) const {
  if (is_eq(x_, p.x_) && is_eq(y_, p.y_) && is_eq(z_, p.z_))
    return true;

  return false;
}

void point_t::print() const {
  std::cout << x_ << " " << y_ << " " << z_ << std::endl;
}

point_t input_point() {
  double x, y, z;
  std::cin >> x >> y >> z;
  assert(std::cin.good());
  point_t res {x, y, z};
  return res;
}
}