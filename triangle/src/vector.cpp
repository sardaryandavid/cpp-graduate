#include "vector.h"

namespace geometry {

bool solve_system(double a1, double a2, double a3, 
                  double b1, double b2, double b3,
                  double& t, double& s, bool& is_inf_sols) {
  double determ = det(a1, a2, b1, b2);

  if (is_eq(determ, 0)) {
    vector_t v1{a1, a2, a3};
    vector_t v2{b1, b2, b3};

    if (v1.is_collinear(v2)) {
      if (!is_eq(a1, 0)) {
        t = a3 / a1;
        s = 0;
      }

      else if (!is_eq(a2, 0)) {
        s = a3 / a2;
        t = 0;
      }

      else if (is_eq(a3, 0) && is_eq(b3, 0)) {
        is_inf_sols = true;
        t = s = 0;
      }
      
      else
        return false;

      return true;
    }

    return false;
  }

  double det1 = det(a3, a2, b3, b2);
  double det2 = det(a1, a3, b1, b3);

  t = det1 / determ;
  s = det2 / determ;

  return true;
}

point_t vector_t::make_point() const {
  point_t p {v_.x_, v_.y_, v_.z_};
  return p;
}

double vector_t::scalar_mult(const vector_t& v) const {
  return v_.x_ * v.v_.x_ + v_.y_ * v.v_.y_ + v_.z_ * v.v_.z_;
}

vector_t vector_t::vector_mult(const vector_t& v) const {
  double res_v1, res_v2, res_v3;
  res_v1 = v_.y_ * v.v_.z_ - v.v_.y_ * v_.z_; 
  res_v2 = v_.z_ * v.v_.x_ - v_.x_ * v.v_.z_;
  res_v3 = v_.x_ * v.v_.y_ - v_.y_ * v.v_.x_;

  vector_t res{res_v1, res_v2, res_v3};
  return res;
}

double vector_t::len() const {
    double len = std::sqrt(scalar_mult(*this));
    return len;
}

vector_t vector_t::normalize() {
  double l = len();
  v_.x_ /= l;
  v_.y_ /= l;
  v_.z_ /= l;
  return *this;
}

vector_t vector_t::operator+(const vector_t& v) const {
  vector_t res{v_.x_ + v.v_.x_, v_.y_ + v.v_.y_, v_.z_ + v.v_.z_};
  return res;
}

vector_t vector_t::operator-(const vector_t& v) const {
  vector_t res{v_.x_ - v.v_.x_, v_.y_ - v.v_.y_, v_.z_ - v.v_.z_};
  return res;
}

vector_t vector_t::operator*(double d) const {
  vector_t res{v_.x_ * d, v_.y_ * d, v_.z_ * d};
  return res;
}

bool vector_t::operator==(const vector_t& v) const {
  if (is_eq(v_.x_, v.v_.x_) &&
      is_eq(v_.y_, v.v_.y_) &&
      is_eq(v_.z_, v.v_.z_))
    return true;
  
  return false;
}

bool vector_t::operator!=(const vector_t& v) const {
  return !(*this == v);
}

bool vector_t::inside(const point_t& min, const point_t& max) const {
  if (min.x_ <= v_.x_ && v_.x_ <= max.x_ &&
      min.y_ <= v_.y_ && v_.y_ <= max.y_ && 
      min.z_ <= v_.z_ && v_.z_ <= max.z_)
    return true;

  return false;
}

bool vector_t::is_collinear(const vector_t& v) const {
  double d1 = v_.x_ * v.v_.y_ - v_.y_ * v.v_.x_;
  double d2 = v_.x_ * v.v_.z_ - v_.z_ * v.v_.x_;
  double d3 = v_.y_ * v.v_.z_ - v_.z_ * v.v_.y_;
  
  if (is_eq(d1, 0) && is_eq(d2, 0) && is_eq(d3, 0))
    return true;

  return false;
}

vector_t vector_t::perp(const vector_t& n) {
  vector_t res = vector_mult(n);
  res.normalize();
  return res;
}

void vector_t::print() const {
  std::cout << v_.x_ << " ";
  std::cout << v_.y_ << " ";
  std::cout << v_.z_ << std::endl;
}
} // geometry