#include "triangle.h"

namespace geometry {

plane_t triangle_t::get_plane() const {
  vector_t v1 = v2_ - v1_;
  vector_t v2 = v3_ - v2_;
  vector_t n = v1.vector_mult(v2);
  n.normalize();
  double d = -(n.v_.x_ * v2.v_.x_ + n.v_.y_ * v2.v_.y_ + n.v_.z_ * v2.v_.z_);
  plane_t res {n, d};
  return res;
}

void triangle_t::compute_interval(const vector_t& d, double& min, double& max) const {
  double s1 = d.scalar_mult(v1_);
  double s2 = d.scalar_mult(v2_);
  double s3 = d.scalar_mult(v3_);

  max = find_fmax(s1, s2, s3);
  min = find_fmin(s1, s2, s3);
}

bool triangle_t::check_d(const triangle_t& t, const vector_t& v1, const vector_t& v2, const plane_t& p) const {
  double min0, max0;
  double min1, max1;
  vector_t v = v2 - v1;
  vector_t d = v.perp(p.n_);
  compute_interval(d, min0, max0);
  t.compute_interval(d, min1, max1);

  if (max1 < min0 || max0 < min1)
    return false;

  return true;
}

bool triangle_t::is_intersect_2d(const triangle_t& t) const {
  plane_t p = t.get_plane();
  if (check_d(t, v1_, v2_, p) && check_d(t, v2_, v3_, p) && check_d(t, v3_, v1_, p) &&
      check_d(t, t.v1_, t.v2_, p) && check_d(t, t.v2_, t.v3_, p) && check_d(t, t.v3_, t.v1_, p))
    return true;

  return false;
}

fig triangle_t::degenerate() const {
  if ((v1_ == v2_) && (v1_ == v3_))
    return point;

  vector_t v1 = v2_ - v1_;
  vector_t v2 = v3_ - v2_;
  vector_t v3 = v1_ - v3_;

  if ((v1_ == v2_) || (v1_ == v3_) || (v2_ == v3_) || 
      v1.is_collinear(v2) || v1.is_collinear(v3) || v2.is_collinear(v3))
    return line;

  return triangle;
}

line_t triangle_t::make_line() const {
  vector_t p = v1_;
  vector_t d;
  if (v1_ != v2_)
    d = v2_ - v1_;

  else
    d = v3_ - v1_;

  line_t l {p, d};
  return l;
}

line_segm_t triangle_t::make_line_segm() const {
  point_t a, b;

  if (v1_ != v2_) {
    a = v1_;
    b = v2_;
  }
  
  else {
    a = v1_;
    b = v3_;
  }
  
  line_segm_t res{a, b};
  return res;
}

point_t triangle_t::min() const {
  double x_min = find_fmin(v1_.x_, v2_.x_, v3_.x_);
  double y_min = find_fmin(v1_.y_, v2_.y_, v3_.y_);
  double z_min = find_fmin(v1_.z_, v2_.z_, v3_.z_);
  
  point_t res{x_min, y_min, z_min};
  return res;
}

point_t triangle_t::max() const {
  double x_max = find_fmax(v1_.x_, v2_.x_, v3_.x_);
  double y_max = find_fmax(v1_.y_, v2_.y_, v3_.y_);
  double z_max = find_fmax(v1_.z_, v2_.z_, v3_.z_);
  
  point_t res{x_max, y_max, z_max};
  return res;
}

point_t triangle_t::min(const triangle_t& t) const {
    point_t pmin1 = min();
    point_t pmin2 = t.min();
    
    double x_min = std::fmin(pmin1.x_, pmin2.x_);
    double y_min = std::fmin(pmin1.y_, pmin2.y_);
    double z_min = std::fmin(pmin1.z_, pmin2.z_);
    
    point_t res{x_min, y_min, z_min};
    return res;
}

point_t triangle_t::max(const triangle_t& t) const {
    point_t pmax1 = max();
    point_t pmax2 = t.max();
    
    double x_max = std::fmax(pmax1.x_, pmax2.x_);
    double y_max = std::fmax(pmax1.y_, pmax2.y_);
    double z_max = std::fmin(pmax1.z_, pmax2.z_);
    
    point_t res{x_max, y_max, z_max};
    return res;
}

bool triangle_t::is_intersect_triangles_3d(const triangle_t& t) const {
  /* Checking corner cases */
  fig f1, f2;
  f1 = degenerate();
  f2 = t.degenerate();

  if ((f1 == point) && (f2 == point)) {
    point_t p1 = v1_;
    point_t p2 = t.v1_;
    return p1.is_intersect_points(p2);
  }

  else if ((f1 == point) && (f2 == line)) {
    point_t p = v1_;
    point_t pmin = t.min();
    point_t pmax = t.max();
    line_t l = t.make_line();
    return l.is_intersect_point_line(p, pmin, pmax);
  }

  else if ((f1 == line) && (f2 == point)) {
    point_t p = t.v1_;
    point_t pmin = min();
    point_t pmax = max();
    line_t l = make_line();
    return l.is_intersect_point_line(p, pmin, pmax);
  }
  
  else if ((f1 == line) && (f2 == line)) {
    line_segm_t ls1 = make_line_segm();
    line_segm_t ls2 = t.make_line_segm();
    return ls1.is_intersect(ls2);
  }
 
  /* Checking triangle intersection */
  return true;
}

void triangle_t::print() const {
  std::cout << v1_.x_ << " " << v1_.y_ << " " << v1_.z_ << " ";
  std::cout << v2_.x_ << " " << v2_.y_ << " " << v2_.z_ << " ";
  std::cout << v3_.x_ << " " << v3_.y_ << " " << v3_.z_ << std::endl;
}
} // geometry