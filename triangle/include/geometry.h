#pragma once

#include <cmath> 
#include <cassert>
#include <iostream>

/* p means plane or point 
 * t means triangle
 * l means line
 * v means vertex or vector
 * d is from the book 
 */

/* Include dependencies:
 * geometry.h -> point.h -> vector.h -> line.h -> plane.h -> triangle.h 
 *                                   -> line_segm.h       -> triangle.h
 */

namespace geometry {
constexpr double acc = 1e-6;

inline double det(double a1, double a2, double b1, double b2) {
  return (a1 * b2 - a2 * b1);
}

inline bool is_eq(double a, double b) {
  return (std::fabs(b - a) < acc);
} 

inline bool is_pos(double a) {
  return (a > acc) ? true : false;
}

inline bool is_neg(double a) {
  return !(is_pos(a) || is_eq(a, 0));
}

inline double find_fmax(double a, double b, double c) {
  return std::fmax(std::fmax(a, b), c);
}

inline double find_fmin(double a, double b, double c) {
  return std::fmin(std::fmin(a, b), c);
}

inline void calculate_intervals(double v1, double v2, double v3,
                                double d1, double d2, double d3,
                                double& t1, double& t2) {
  t1 = v1 + (v3 - v1) * (d1 / (d1 - d3));
  t2 = v2 + (v3 - v2) * (d2 / (d2 - d3));
}

inline void calculate_intervals_wrap(double v1, double v2, double v3,
                                    double d1, double d2, double d3,
                                    double& t1, double& t2) {
  #ifdef DEBUG
  std::cout << "In calculate_intervals_wrap\n";
  std::cout << "v1 = " << v1 << " v2 = " << v2 << " v3 = " << v3 << "\n";
  std::cout << "d1 = " << d1 << " d2 = " << d2 << " d3 = " << d3 << "\n";
  #endif

  if (is_pos(d1 * d2) || is_eq(d1, 0) || is_eq(d2, 0))
    calculate_intervals(v1, v2, v3, d1, d2, d3, t1, t2);

  else if (is_pos(d1 * d3) || is_eq(d3, 0))
    calculate_intervals(v1, v3, v2, d1, d3, d2, t1, t2);

  else
    calculate_intervals(v2, v3, v1, d2, d3, d1, t1, t2);
}
} // geometry