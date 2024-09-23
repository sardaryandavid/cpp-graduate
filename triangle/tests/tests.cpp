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

  ASSERT_TRUE(t1.is_intersect_2d(t2));
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

  ASSERT_TRUE(!t1.is_intersect_2d(t2));
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

  ASSERT_TRUE(t1.is_intersect_2d(t2));
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

  ASSERT_TRUE(t1.is_intersect_2d(t2));
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

  ASSERT_TRUE(t1.is_intersect_2d(t2));
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

  ASSERT_TRUE(t.degenerate() == geometry::line);
}

TEST(triangle, degenerate_to_line_2) {
  geometry::point_t p1 {2.5, 5, 0};
  geometry::point_t p2 {5, 10, 0};
  geometry::point_t p3 {10, 20, 0};
  geometry::triangle_t t {p1, p2, p3};

  ASSERT_TRUE(t.degenerate() == geometry::line);
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

  ASSERT_TRUE(t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(!t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(!t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(!t1.is_intersect_triangles_3d(t2));
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

  ASSERT_TRUE(t1.is_intersect_triangles_3d(t2));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}