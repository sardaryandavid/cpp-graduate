#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "triangle.h"


/* Vector tests */
TEST(vector, constructor_1) {
  geometry::vector_t v{1, -0.33, 1.22};

  ASSERT_TRUE(geometry::is_eq(v.v_.x_, 1));
  ASSERT_TRUE(geometry::is_eq(v.v_.y_, -0.33));
  ASSERT_TRUE(geometry::is_eq(v.v_.z_, 1.22));
}

TEST(vector, scalar_mult_1) {
  geometry::vector_t v1{1, -2, 5};
  geometry::vector_t v2{3, 6, -0.5};
  double res = v1.scalar_mult(v2);
  double ans = -11.5;

  ASSERT_TRUE(geometry::is_eq(res, ans));
}

TEST(vector, scalar_mult_2) {
  geometry::vector_t v1{0, 2, 0.2};
  geometry::vector_t v2{1, 5, -4};
  double res = v1.scalar_mult(v2);
  double ans = 9.2;

  ASSERT_TRUE(geometry::is_eq(res, ans));
}

TEST(vector, scalar_mult_3) {
  geometry::vector_t v1{1.123, -141.12, 413.13};
  geometry::vector_t v2{12.543, -0.03, 4.213};
  double res = v1.scalar_mult(v2);
  double ans = 1758.836079;

  ASSERT_TRUE(geometry::is_eq(res, ans));
}

TEST(vector, vector_mult_1) {
  geometry::vector_t v1{1.123, -141.12, 413.13};
  geometry::vector_t v2{12.543, -0.03, 4.213};
  geometry::vector_t res = v1.vector_mult(v2);
  geometry::vector_t ans {-582.14466, 5177.158391, 1770.03447};

   ASSERT_TRUE(res == ans); 
}

TEST(vector, operator_minus_1) {
  geometry::vector_t v1{1.123, -141.12, 413.13};
  geometry::vector_t v2{12.543, -0.03, 4.213};
  geometry::vector_t res = v1 - v2;
  geometry::vector_t ans {-11.42, -141.09, 408.917};

   ASSERT_TRUE(res == ans); 
}

TEST(vector, operator_plus_1) {
  geometry::vector_t v1{1.123, -141.12, 413.13};
  geometry::vector_t v2{12.543, -0.03, 4.213};
  geometry::vector_t res = v1 + v2;
  geometry::vector_t ans {13.666, -141.15, 417.343};

   ASSERT_TRUE(res == ans); 
}

TEST(vector, is_collinear_1) {
  geometry::vector_t v1{0.5, -3, 2.5};
  geometry::vector_t v2{5, -30, 25};

   ASSERT_TRUE(v1.is_collinear(v2)); 
}

/* Triangle tests */

TEST(triangle, get_plane_1) {
  geometry::point_t p1 {0, 0, 0};
  geometry::point_t p2 {0, 2, 0};
  geometry::point_t p3 {2, 0, 0};
  geometry::triangle_t t {p1, p2, p3};
  
  geometry::plane_t p = t.get_plane(); 
  geometry::vector_t n {0, 0, 1};
  ASSERT_TRUE(n.is_collinear(p.n_));
  ASSERT_TRUE(geometry::is_eq(p.d_, 0));
}

TEST(triangle, get_plane_2) {
  geometry::point_t p1 {2, -3, 4};
  geometry::point_t p2 {1, 4, 6};
  geometry::point_t p3 {5, 3, -1};
  geometry::triangle_t t {p1, p2, p3};
  
  geometry::plane_t p = t.get_plane(); 
  geometry::vector_t n {-47, 1, -27};
  double l = n.len();

  ASSERT_TRUE(n.is_collinear(p.n_));
  ASSERT_TRUE(geometry::is_eq(p.d_, 205.0 / l));
}


TEST(triangle, compute_interval_1) {
  geometry::point_t p1 {0, 0, 0};
  geometry::point_t p2 {0, 2, 0};
  geometry::point_t p3 {2, 0, 0};
  geometry::triangle_t t {p1, p2, p3};
  double min, max;
  geometry::vector_t v {1, 0, 0};
  t.compute_interval(v, min, max);

  ASSERT_TRUE(geometry::is_eq(min, 0));
  ASSERT_TRUE(geometry::is_eq(max, 2));
}

TEST(triangle, intersection_2d_1) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 2, 0};
  geometry::point_t t1p3 {0, 0, 0};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {2, 2, 0};
  geometry::point_t t2p3 {2, 0, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_2d(t2));
}

TEST(triangle, intersection_2d_2) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 2, 0};
  geometry::point_t t1p3 {0, 0, 0};
  geometry::point_t t2p1 {3, 0, 0};
  geometry::point_t t2p2 {5, 2, 0};
  geometry::point_t t2p3 {6, 0, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_2d(t2));
}

TEST(triangle, intersection_2d_3) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 2, 0};
  geometry::point_t t1p3 {0, 0, 0};
  geometry::point_t t2p1 {-1, 0, 0};
  geometry::point_t t2p2 {3, 2, 0};
  geometry::point_t t2p3 {6, 2, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_2d(t2));
}

TEST(triangle, intersection_2d_4) {
  geometry::point_t t1p1 {0.4, -5, 0};
  geometry::point_t t1p2 {1, 2, 0};
  geometry::point_t t1p3 {5, 0, 0};
  geometry::point_t t2p1 {-1, 0, 0};
  geometry::point_t t2p2 {3, 2, 0};
  geometry::point_t t2p3 {6, 2, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_2d(t2));
}

TEST(triangle, intersection_2d_5) {
  geometry::point_t t1p1 {1, 0, 1};
  geometry::point_t t1p2 {1, 0, 5};
  geometry::point_t t1p3 {5, 0, 4};
  geometry::point_t t2p1 {5, 0, 2};
  geometry::point_t t2p2 {2.1, 0, 8};
  geometry::point_t t2p3 {1, 0, -1};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_2d(t2));
}

TEST(triangle, triangle_intersection_with_point_1) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0.5, 0.5};
  geometry::point_t t2p2 {0, 0.5, 0.5};
  geometry::point_t t2p3 {0, 0.5, 0.5};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_point_2) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0.25, 0.33};
  geometry::point_t t2p2 {0, 0.25, 0.33};
  geometry::point_t t2p3 {0, 0.25, 0.33};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_point_3) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0.1, 0.25, 0.33};
  geometry::point_t t2p2 {0.1, 0.25, 0.33};
  geometry::point_t t2p3 {0.1, 0.25, 0.33};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_point_4) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {0, 0, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_point_5) {
  geometry::point_t t1p1 {0, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {0, 0, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_point_6) {
  geometry::point_t t1p1 {2, -2, -1};
  geometry::point_t t1p2 {1, 1, -1};
  geometry::point_t t1p3 {2, 2, 1};
  geometry::point_t t2p1 {2, 0, 0};
  geometry::point_t t2p2 {2, 0, 0};
  geometry::point_t t2p3 {2, 0, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_1) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {1, 1, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_2) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {1, 1, 1};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_3) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {-1, 1, 1};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_4) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {0, 0, 0};
  geometry::point_t t2p3 {0.25, 0.25, 0.25};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_5) {
  geometry::point_t t1p1 {5, 3, 2};
  geometry::point_t t1p2 {1, 1, 0};
  geometry::point_t t1p3 {-2, 3, 1};
  geometry::point_t t2p1 {6, 3, 2};
  geometry::point_t t2p2 {1, 3, 0};
  geometry::point_t t2p3 {1, 3, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_6) {
  geometry::point_t t1p1 {5, 3, 2};
  geometry::point_t t1p2 {1, 1, 0};
  geometry::point_t t1p3 {-2, 3, 1};
  geometry::point_t t2p1 {6, 2, 7};
  geometry::point_t t2p2 {1, 3, 0};
  geometry::point_t t2p3 {1, 3, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, triangle_intersection_with_line_segm_7) {
  geometry::point_t t1p1 {2, 0, 0};
  geometry::point_t t1p2 {0, 2, 0};
  geometry::point_t t1p3 {0, 0, 0};
  geometry::point_t t2p1 {0.5, 0.5, 0.5};
  geometry::point_t t2p2 {0.5, 0.5, 1};
  geometry::point_t t2p3 {0.5, 0.5, 1};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, degenerate_to_point_1) {
  geometry::point_t p1 {1.12, -3.52, 1.12};
  geometry::point_t p2 {1.12, -3.52, 1.12};
  geometry::point_t p3 {1.12, -3.52, 1.12};
  geometry::triangle_t t {p1, p2, p3};

  ASSERT_TRUE(t.degenerate() == geometry::point);
}

TEST(triangle, degenerate_to_line_1) {
  geometry::point_t p1 {1.41, 2.345, 3.645};
  geometry::point_t p2 {1.41, 2.345, 3.645};
  geometry::point_t p3 {5.23, 41.141, 8.23};
  geometry::triangle_t t {p1, p2, p3};

  ASSERT_TRUE(t.degenerate() == geometry::line_segm);
}

TEST(triangle, degenerate_to_line_2) {
  geometry::point_t p1 {2.5, 5, 0};
  geometry::point_t p2 {5, 10, 0};
  geometry::point_t p3 {10, 20, 0};
  geometry::triangle_t t {p1, p2, p3};

  ASSERT_TRUE(t.degenerate() == geometry::line_segm);
}

TEST(triangle, not_degenerate_1) {
  geometry::point_t p1 {2.5, 5, 234.252};
  geometry::point_t p2 {5.1234, 10.141, -4213.1};
  geometry::point_t p3 {-14.11, 8.44, 1.41};
  geometry::triangle_t t {p1, p2, p3};

  ASSERT_TRUE(t.degenerate() == geometry::triangle);
}

TEST(triangle, make_line_1) {
  geometry::point_t p1 {2.5, 5, 0};
  geometry::point_t p2 {5, 10, 0};
  geometry::point_t p3 {10, 20, 0};
  geometry::triangle_t t {p1, p2, p3};
  geometry::line_t l = t.make_line();

  geometry::vector_t ans_p {2.5, 5, 0};
  geometry::vector_t ans_d {2.5, 5, 0};

  ASSERT_TRUE(l.p_ == ans_p);
  ASSERT_TRUE(l.d_ == ans_d);
}

TEST(triangle, make_line_2) {
  geometry::point_t p1 {2.5, 5, 0};
  geometry::point_t p2 {2.5, 5, 0};
  geometry::point_t p3 {10, 20, 0};
  geometry::triangle_t t {p1, p2, p3};
  geometry::line_t l = t.make_line();

  geometry::vector_t ans_p {2.5, 5, 0};
  geometry::vector_t ans_d {7.5, 15, 0};

  ASSERT_TRUE(l.p_ == ans_p);
  ASSERT_TRUE(l.d_ == ans_d);
}

TEST(triangle, intersection_3d_points_intersection_1) {
  geometry::point_t t1p1 {1.421, 14.124, -6.245};
  geometry::point_t t1p2 {1.421, 14.124, -6.245};
  geometry::point_t t1p3 {1.421, 14.124, -6.245};
  geometry::point_t t2p1 {1.421, 14.124, -6.245};
  geometry::point_t t2p2 {1.421, 14.124, -6.245};
  geometry::point_t t2p3 {1.421, 14.124, -6.245};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_and_point_intersection_1) {
  geometry::point_t t1p1 {2.5, 5, 3};
  geometry::point_t t1p2 {5, 10, 6};
  geometry::point_t t1p3 {5, 10, 6};
  geometry::point_t t2p1 {3.75, 7.5, 4.5};
  geometry::point_t t2p2 {3.75, 7.5, 4.5};
  geometry::point_t t2p3 {3.75, 7.5, 4.5};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_and_point_intersection_3) {
  geometry::point_t t1p1 {2.5, 5, 3};
  geometry::point_t t1p2 {5, 10, 6};
  geometry::point_t t1p3 {25, 50, 30};
  geometry::point_t t2p1 {3.75, 7.5, 4.5};
  geometry::point_t t2p2 {3.75, 7.5, 4.5};
  geometry::point_t t2p3 {3.75, 7.5, 4.5};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_and_point_intersection_2) {
  geometry::point_t t1p1 {2.5, 5, 3};
  geometry::point_t t1p2 {5, 10, 6};
  geometry::point_t t1p3 {5, 10, 6};
  geometry::point_t t2p1 {41.1, 7.5, 4.5};
  geometry::point_t t2p2 {41.1, 7.5, 4.5};
  geometry::point_t t2p3 {41.1, 7.5, 4.5};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_intersection_1) {
  geometry::point_t t1p1 {2.5, 5, 0};
  geometry::point_t t1p2 {5, 10, 0};
  geometry::point_t t1p3 {5, 10, 0};
  geometry::point_t t2p1 {-2, 10, 0};
  geometry::point_t t2p2 {20, -4, 0};
  geometry::point_t t2p3 {20, -4, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_intersection_2) {
  geometry::point_t t1p1 {2.5, 5, 0};
  geometry::point_t t1p2 {5, 10, 0};
  geometry::point_t t1p3 {5, 10, 0};
  geometry::point_t t2p1 {-20, 10, 0};
  geometry::point_t t2p2 {20, -4, 0};
  geometry::point_t t2p3 {20, -4, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_intersection_3) {
  geometry::point_t t1p1 {2.123, -2.52, 0};
  geometry::point_t t1p2 {5.31, 141, 0};
  geometry::point_t t1p3 {5.31, 141, 0};
  geometry::point_t t2p1 {-20, 10, 0};
  geometry::point_t t2p2 {20, -50, 0};
  geometry::point_t t2p3 {20, -50, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_line_intersection_4) {
  geometry::point_t t1p1 {2.123, -2.52, 0};
  geometry::point_t t1p2 {5.31, 141, 0};
  geometry::point_t t1p3 {5.31, 141, 0};
  geometry::point_t t2p1 {-20, 10, 0};
  geometry::point_t t2p2 {20, -3, 0};
  geometry::point_t t2p3 {20, -3, 0};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_1) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {1, 1, 1};
  geometry::point_t t2p3 {-2, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_2) {
  geometry::point_t t1p1 {1, 0, 0};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {1, 1, 1};
  geometry::point_t t2p3 {-2, 2, 20};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_3) {
  geometry::point_t t1p1 {-1, 5, 4};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {0, 0, 0};
  geometry::point_t t2p2 {1, 1, 1};
  geometry::point_t t2p3 {-2, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_4) {
  geometry::point_t t1p1 {-1, 5, 4};
  geometry::point_t t1p2 {0, 1, 0};
  geometry::point_t t1p3 {0, 0, 1};
  geometry::point_t t2p1 {-1, -2, -1};
  geometry::point_t t2p2 {-1, -1, -1};
  geometry::point_t t2p3 {-2, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_5) {
  geometry::point_t t1p1 {2, -3, 7};
  geometry::point_t t1p2 {1, 4, 6};
  geometry::point_t t1p3 {5, 3, -1};
  geometry::point_t t2p1 {1, 1, 1};
  geometry::point_t t2p2 {1, 0, 1};
  geometry::point_t t2p3 {1, -1, 3};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_6) {
  geometry::point_t t1p1 {2, -3, 4};
  geometry::point_t t1p2 {1, 4, 6};
  geometry::point_t t1p3 {5, 3, -1};
  geometry::point_t t2p1 {-1, 5, 2};
  geometry::point_t t2p2 {2, -1, 4};
  geometry::point_t t2p3 {5, 0, 5};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_7) {
  geometry::point_t t1p1 {2.5, 5.234, -4.234};
  geometry::point_t t1p2 {1.31, 5.01, -1.14};
  geometry::point_t t1p3 {-1.1, -2.4, 5};
  geometry::point_t t2p1 {1.5, 2.1, 3.1};
  geometry::point_t t2p2 {-1.5, -5.1, 2};
  geometry::point_t t2p3 {4.1, 5, 3};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_8) {
  geometry::point_t t1p1 {2.2, 5.3, -4.2};
  geometry::point_t t1p2 {1, 1, -1};
  geometry::point_t t1p3 {2, 2, 2};
  geometry::point_t t2p1 {5, 5, 0};
  geometry::point_t t2p2 {1, 1, 1};
  geometry::point_t t2p3 {-3, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_9) {
  geometry::point_t t1p1 {2.2, 5.3, -4.2};
  geometry::point_t t1p2 {1, 1, -1};
  geometry::point_t t1p3 {2, 2, 2};
  geometry::point_t t2p1 {5, 5, 0};
  geometry::point_t t2p2 {2, 2, 2};
  geometry::point_t t2p3 {-3, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_10) {
  geometry::point_t t1p1 {2.2, 5.3, -4.2};
  geometry::point_t t1p2 {1, 1, -1};
  geometry::point_t t1p3 {-2, -2, -2};
  geometry::point_t t2p1 {5, 5, 0};
  geometry::point_t t2p2 {1, 1, -1};
  geometry::point_t t2p3 {-3, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_11) {
  geometry::point_t t1p1 {18, 1, 20};
  geometry::point_t t1p2 {9, 7, 1};
  geometry::point_t t1p3 {3, 19, 6};
  geometry::point_t t2p1 {3, 4, 9};
  geometry::point_t t2p2 {9, 4, 16};
  geometry::point_t t2p3 {16, 4, 6};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_12) {
  geometry::point_t t1p1 {18, 1, 20};
  geometry::point_t t1p2 {9, 7, 1};
  geometry::point_t t1p3 {3, 19, 6};
  geometry::point_t t2p1 {5, 16, 16};
  geometry::point_t t2p2 {19, 3, 16};
  geometry::point_t t2p3 {3, 2, 2};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_13) {
  geometry::point_t t1p1 {18, 1, 20};
  geometry::point_t t1p2 {9, 7, 1};
  geometry::point_t t1p3 {3, 19, 6};
  geometry::point_t t2p1 {2, 17, 18};
  geometry::point_t t2p2 {9, 20, 3};
  geometry::point_t t2p3 {14, 6, 14};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_15) {
  geometry::point_t t1p1 {18, 1, 20};
  geometry::point_t t1p2 {9, 7, 1};
  geometry::point_t t1p3 {3, 19, 6};
  geometry::point_t t2p1 {12, 7, 6};
  geometry::point_t t2p2 {12, 16, 7};
  geometry::point_t t2p3 {13, 15, 11};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(!t1.is_intersect_triangle_3d(t2));
}

TEST(triangle, intersection_3d_16) {
  geometry::point_t t1p1 {18, 1, 20};
  geometry::point_t t1p2 {9, 7, 1};
  geometry::point_t t1p3 {3, 19, 6};
  geometry::point_t t2p1 {12, 4, 10};
  geometry::point_t t2p2 {17, 20, 13};
  geometry::point_t t2p3 {18, 10, 6};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  ASSERT_TRUE(t1.is_intersect_triangle_3d(t2));
}

/* Plane tests */

TEST(plane, coincident_1) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {1, 1, 1, -2};

  ASSERT_TRUE(p1.is_coincident(p2));
}

TEST(plane, coincident_2) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -10};

  ASSERT_TRUE(p1.is_coincident(p2));
}

TEST(plane, coincident_3) {
  geometry::plane_t p1 {2, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -10};

  ASSERT_TRUE(!p1.is_coincident(p2));
}

TEST(plane, coincident_4) {
  geometry::point_t t1p1 {2.5, 5.234, -4.234};
  geometry::point_t t1p2 {1.31, 5.01, -1.14};
  geometry::point_t t1p3 {-1.1, -2.4, 5};
  geometry::point_t t2p1 {1.5, 2.1, 3.1};
  geometry::point_t t2p2 {-1.5, -5.1, 2};
  geometry::point_t t2p3 {4.1, 5, 3};
  geometry::triangle_t t1 {t1p1, t1p2, t1p3};
  geometry::triangle_t t2 {t2p1, t2p2, t2p3};

  geometry::plane_t p1 = t1.get_plane();
  geometry::plane_t p2 = t2.get_plane();

  ASSERT_TRUE(!p1.is_coincident(p2));
}

TEST(plane, signed_distance_to_point_1) {
  geometry::point_t p1 {1, 0, 0};
  geometry::point_t p2 {1, 1, 0};
  geometry::point_t p3 {-1, 0, 0};
  geometry::triangle_t t {p1, p2, p3};

  geometry::point_t pt {0, 0, 1.5};
  geometry::plane_t p = t.get_plane();

  ASSERT_TRUE(geometry::is_eq(p.signed_distance_to_point(pt), 1.5));
}

TEST(plane, signed_distance_to_point_2) {
  geometry::point_t p1 {1, -1, 0};
  geometry::point_t p2 {1, 1, 0};
  geometry::point_t p3 {0, 0, 1};
  geometry::triangle_t t {p1, p2, p3};

  geometry::point_t pt {0, 0, 0};
  geometry::plane_t p = t.get_plane();
  
  ASSERT_TRUE(geometry::is_eq(p.signed_distance_to_point(pt), -0.707106));
}

TEST(plane, is_parallel_1) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -10};
  
  ASSERT_TRUE(p1.is_parallel(p2));
}

TEST(plane, is_parallel_2) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -2};
  
  ASSERT_TRUE(p1.is_parallel(p2));
}

TEST(plane, is_parallel_3) {
  geometry::plane_t p1 {1.01, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -2};
  
  ASSERT_TRUE(!p1.is_parallel(p2));
}

TEST(plane, plane_intersection_1) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -2};
  geometry::line_t l;

  ASSERT_TRUE(!p1.plane_intersection(p2, l));
}

TEST(plane, plane_intersection_2) {
  geometry::plane_t p1 {1, 1, 1, -2};
  geometry::plane_t p2 {5, 5, 5, -3};
  geometry::line_t l;

  ASSERT_TRUE(!p1.plane_intersection(p2, l));
}

TEST(plane, plane_intersection_3) {
  geometry::plane_t p1 {2, -1, 3, 4};
  geometry::plane_t p2 {1, 5, -3, -7};
  geometry::line_t l;

  ASSERT_TRUE(p1.plane_intersection(p2, l));
  ASSERT_TRUE(geometry::is_eq(l.d_.v_.x_, -12));
  ASSERT_TRUE(geometry::is_eq(l.d_.v_.y_, 9));
  ASSERT_TRUE(geometry::is_eq(l.d_.v_.z_, 11));
  ASSERT_TRUE(geometry::is_eq(l.p_.v_.x_, -0.179191));
  ASSERT_TRUE(geometry::is_eq(l.p_.v_.y_, 0.884393));
  ASSERT_TRUE(geometry::is_eq(l.p_.v_.z_, -0.919075));

}

/* Line segment tests */

TEST(line_segm, intersect_1) {
  geometry::point_t p00 {1, 1, 0};
  geometry::point_t p01 {2, 2, 0};
  geometry::point_t p10 {3, 3, 0};
  geometry::point_t p11 {4, 4, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(!ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_2) {
  geometry::point_t p00 {1.54, 2.56, 6.42};
  geometry::point_t p01 {8.64, 1.35, 8};
  geometry::point_t p10 {-1.24, -42.2, -1};
  geometry::point_t p11 {-5, -1.11, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(!ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_3) {
  geometry::point_t p00 {1, 1, 1};
  geometry::point_t p01 {2, 2, 2};
  geometry::point_t p10 {0.5, 0.5, 0.5};
  geometry::point_t p11 {1, 3, 4};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(!ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_4) {
  geometry::point_t p00 {1, 1, 1};
  geometry::point_t p01 {2, 2, 2};
  geometry::point_t p10 {0.5, 0.5, 5};
  geometry::point_t p11 {2, 2, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_5) {
  geometry::point_t p00 {1, 1, 0};
  geometry::point_t p01 {2, 2, 0};
  geometry::point_t p10 {1, 2, 0};
  geometry::point_t p11 {2, 1, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_6) {
  geometry::point_t p00 {0.5, 0.5, 5};
  geometry::point_t p01 {2, 2, 0};
  geometry::point_t p10 {-1, -1, 5};
  geometry::point_t p11 {2, 2, 5};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_7) {
  geometry::point_t p00 {-0.306323, 0, 0};
  geometry::point_t p01 {-0.754018, 0, 0};
  geometry::point_t p10 {1.16577, 0, 0};
  geometry::point_t p11 {0.629974, 0, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(!ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_8) {
  geometry::point_t p00 {3.56859, 0, 0};
  geometry::point_t p01 {0.696311, 0, 0};
  geometry::point_t p10 {0.121854, 0, 0};
  geometry::point_t p11 {2.00189, 0, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_9) {
  geometry::point_t p00 {-3.15296, 0, 0};
  geometry::point_t p01 {-2.01166, 0, 0};
  geometry::point_t p10 {-2.01166, 0, 0};
  geometry::point_t p11 {-4.70657, 0, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

TEST(line_segm, intersect_10) {
  geometry::point_t p00 {-3.37953, 0, 0};
  geometry::point_t p01 {1.15599, 0, 0};
  geometry::point_t p10 {6.49243, 0, 0};
  geometry::point_t p11 {1.15599, 0, 0};
  geometry::line_segm_t ls1 {p00, p01};
  geometry::line_segm_t ls2 {p10, p11};

  ASSERT_TRUE(ls1.is_intersect_line_segm(ls2));
}

/* Geometry tests */

TEST(geometry, solve_system_1) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(2.4, -5.2, 9, -1, 2.5, -1, t, s, b);
  ASSERT_TRUE(geometry::is_eq(t, 21.625));
  ASSERT_TRUE(geometry::is_eq(s, 8.25));
  ASSERT_TRUE(res);
}

TEST(geometry, solve_system_2) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(1, 1, 1, 1, 1, 1, t, s, b);
  ASSERT_TRUE(geometry::is_eq(t, 1));
  ASSERT_TRUE(geometry::is_eq(s, 0));
  ASSERT_TRUE(res);
}

TEST(geometry, solve_system_3) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(0, 1, 1, 0, 1, 1, t, s, b);
  ASSERT_TRUE(geometry::is_eq(t, 0));
  ASSERT_TRUE(geometry::is_eq(s, 1));
  ASSERT_TRUE(res);
}

TEST(geometry, solve_system_4) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(0, 0, 1, 0, 0, 1, t, s, b);
  ASSERT_TRUE(!res);
}

TEST(geometry, solve_system_5) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(0, 0, 0, 0, 0, 0, t, s, b);
  ASSERT_TRUE(geometry::is_eq(t, 0));
  ASSERT_TRUE(geometry::is_eq(s, 0));
  ASSERT_TRUE(res);
}

TEST(geometry, solve_system_6) {
  double t, s;
  bool b;
  bool res = geometry::solve_system(1, 1, 2, 1, 1, 3, t, s, b);
  ASSERT_TRUE(!res);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}