#include "triangle.h"

namespace geometry {

static bool on_one_side(double d1, double d2, double d3) {
  return ((is_pos(d1) && is_pos(d2) && is_pos(d3)) || 
          (is_neg(d1) && is_neg(d2) && is_neg(d3)));
}

static double signed_volume(const vector_t& a, const vector_t& b, 
                            const vector_t& c, const vector_t& d) {
  vector_t v1 = b - a;
  vector_t v2 = c - a;
  vector_t v3 = d - a;
  return 1.0 * v3.scalar_mult(v1.vector_mult(v2)) / 6.0;
}

plane_t triangle_t::get_plane() const {
  vector_t v1 = v2_ - v1_;
  vector_t v2 = v3_ - v2_;
  vector_t n = v1.vector_mult(v2);
  n.normalize();
  double d = -(n.v_.x_ * v2_.x_ + n.v_.y_ * v2_.y_ + n.v_.z_ * v2_.z_);
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

bool triangle_t::is_intersect_point(const point_t& p) const {
  plane_t pl = get_plane();
  if (is_pos(pl.signed_distance_to_point(p)))
    return false;

  vector_t b = v2_ - v1_;
  vector_t c = v3_ - v1_;
  vector_t vp = p - v1_;
  
  double pc = vp.scalar_mult(c);
  double pb = vp.scalar_mult(b);
  double b_norm = b.scalar_mult(b);
  double c_norm = c.scalar_mult(c);
  double bc = b.scalar_mult(c);
  double den = c_norm * b_norm - bc * bc;

  double m = (pc * b_norm - pb * bc) / den;
  double l = (pb * c_norm - pc * bc) / den;

  return (is_nneg(l) && is_npos(l - 1) && is_nneg(m) && is_npos(m - 1) && is_npos(l + m - 1));
}

/* Algorithm here:
 * https://stackoverflow.com/questions/42740765/intersection-between-line-and-triangle-in-3d */
bool triangle_t::is_intersect_line_segm(const line_segm_t& ls) const {
  bool b1 = is_npos(signed_volume(ls.a_, v1_, v2_, v3_) * signed_volume(ls.b_, v1_, v2_, v3_));
  bool b2 = is_nneg(signed_volume(ls.a_, ls.b_, v1_, v2_) * signed_volume(ls.a_, ls.b_, v2_, v3_));
  bool b3 = is_nneg(signed_volume(ls.a_, ls.b_, v1_, v2_) * signed_volume(ls.a_, ls.b_, v3_, v1_));
  vector_t v1 = v2_ - v1_;
  vector_t v2 = v3_ - v1_;
  vector_t n = v1.vector_mult(v2);
  double t = -n.scalar_mult(ls.a_ - v1_) / n.scalar_mult(ls.b_ - ls.a_);
  return (b1 && b2 && b3 && is_nneg(t) && is_npos(t - 1));
}

bool triangle_t::is_intersect_triangle_2d(const triangle_t& t) const {
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
    return line_segm;

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

bool triangle_t::check_corner_cases(const triangle_t& t, bool& is_corner_case) const {
  is_corner_case = false;

  fig f1, f2;
  f1 = degenerate();
  f2 = t.degenerate();

  if (f1 == point) {
    is_corner_case = true;
    point_t p1 = v1_;
    if (f2 == point) {
      point_t p2 = t.v1_;
      return p1.is_intersect_point(p2);
    }

    else if (f2 == line_segm) {
      line_segm_t ls = t.make_line_segm();
      return ls.is_intersect_point(p1);
    }

    else {
      return t.is_intersect_point(p1);
    }
  }

  else if (f1 == line_segm) {
    is_corner_case = true;
    line_segm_t ls1 = make_line_segm();

    if (f2 == point) {
      point_t p = t.v1_;
      return ls1.is_intersect_point(p);
    }

    else if (f2 == line_segm) {
      line_segm_t ls2 = t.make_line_segm();
      return ls1.is_intersect_line_segm(ls2);
    }

    else {
      return t.is_intersect_line_segm(ls1);
    }
  }

  else {
    if (f2 == point) {
      is_corner_case = true;
      point_t p2 = t.v1_;
      return is_intersect_point(p2);
    }

    else if (f2 == line_segm) {
      is_corner_case = true;
      line_segm_t ls2 = t.make_line_segm();
      return is_intersect_line_segm(ls2);
    }
  }

  return false;
}

bool triangle_t::is_intersect_triangle_3d(const triangle_t& t) const {
  /* Checking corner cases */
  bool is_corner_case;
  bool res = check_corner_cases(t, is_corner_case);

  if (is_corner_case)
    return res;
  
  /* Checking triangle intersection */
  plane_t p0 = get_plane();

  double d11 = p0.signed_distance_to_point(t.v1_);
  double d12 = p0.signed_distance_to_point(t.v2_);
  double d13 = p0.signed_distance_to_point(t.v3_);

  if (on_one_side(d11, d12, d13))
    return false;
  
  plane_t p1 = t.get_plane();
  
  if (p0.is_coincident(p1))
    return is_intersect_triangle_2d(t);
  
  else if (p0.is_parallel(p1))
    return false;

  double d01 = p1.signed_distance_to_point(v1_);
  double d02 = p1.signed_distance_to_point(v2_);
  double d03 = p1.signed_distance_to_point(v3_);

  if (on_one_side(d01, d02, d03))
    return false;

  line_t l;
  p0.plane_intersection(p1, l);

  double v01 = l.d_.scalar_mult(l.p_ - v1_);
  double v02 = l.d_.scalar_mult(l.p_ - v2_);
  double v03 = l.d_.scalar_mult(l.p_ - v3_);
  double v11 = l.d_.scalar_mult(l.p_ - t.v1_);
  double v12 = l.d_.scalar_mult(l.p_ - t.v2_);
  double v13 = l.d_.scalar_mult(l.p_ - t.v3_);
  double t00, t01, t10, t11;

  calculate_intervals_wrap(v01, v02, v03, d01, d02, d03, t00, t01);
  calculate_intervals_wrap(v11, v12, v13, d11, d12, d13, t10, t11);

  point_t p00 {t00, 0, 0};
  point_t p01 {t01, 0, 0};
  point_t p10 {t10, 0, 0};
  point_t p11 {t11, 0, 0};

  line_segm_t ls1 {p00, p01};
  line_segm_t ls2 {p10, p11};

  if (!ls1.is_intersect_line_segm(ls2))
    return false;

  return true;
}

triangle_t input_triangle() {
  point_t v1 = input_point();
  point_t v2 = input_point();
  point_t v3 = input_point();
  triangle_t res {v1, v2, v3};
  return res;
}

void triangle_t::print() const {
  std::cout << v1_.x_ << " " << v1_.y_ << " " << v1_.z_ << " ";
  std::cout << v2_.x_ << " " << v2_.y_ << " " << v2_.z_ << " ";
  std::cout << v3_.x_ << " " << v3_.y_ << " " << v3_.z_ << std::endl;
}
} // geometry