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

/* TODO: find all functions to include to .h */
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

inline bool is_npos(double a) {
  return !(is_pos(a));
}

inline bool is_nneg(double a) {
  return !(is_neg(a));
}

inline double find_fmax(double a, double b, double c) {
  return std::fmax(std::fmax(a, b), c);
}

inline double find_fmin(double a, double b, double c) {
  return std::fmin(std::fmin(a, b), c);
}

/* Use only if d1 * d3 <= 0, d2 * d3 <= 0, d3 != 0 */
inline void calculate_intervals(double v1, double v2, double v3,
                                double d1, double d2, double d3,
                                double& t1, double& t2) {
  t1 = v1 + (v3 - v1) * (d1 / (d1 - d3));
  t2 = v2 + (v3 - v2) * (d2 / (d2 - d3));
}

/* Use only if d1 * d2 <= 0 or d1 * d3 <= 0 or d2 * d3 <= 0 and cannot be d1 = d2 = d3 = 0 */
inline void calculate_intervals_wrap(double v1, double v2, double v3,
                                     double d1, double d2, double d3,
                                     double& t1, double& t2) {
  if ((is_pos(d1 * d2) && !is_eq(d3, 0)) || 
      (is_eq(d1, 0) && is_neg(d2 * d3)) || 
      (is_eq(d2, 0) && is_neg(d1 * d3)))
    calculate_intervals(v1, v2, v3, d1, d2, d3, t1, t2);

  else if ((is_pos(d1 * d3) && !is_eq(d2, 0)) || 
           (is_eq(d3, 0) && is_neg(d1 * d2)))
    calculate_intervals(v1, v3, v2, d1, d3, d2, t1, t2);

  else if (is_pos(d2 * d3) && !is_eq(d1, 0))
    calculate_intervals(v2, v3, v1, d2, d3, d1, t1, t2);

  else if (is_eq(d1, 0)) {
    if (is_eq(d2, 0)) {
      t2 = std::max(v1, v2);
      t1 = std::min(v1, v2);
    }

    else if (is_eq(d3, 0)) {
      t2 = std::max(v1, v3);
      t1 = std::min(v1, v3);
    }

    else
      t1 = t2 = v1;
  }

  else if (is_eq(d2, 0)) {
    if (is_eq(d3, 0)) {
      t2 = std::max(v2, v3);
      t1 = std::min(v2, v3);
    }

    else
      t1 = t2 = v2;
  }

  else if (is_eq(d3, 0))
    t1 = t2 = v3;
}
} // geometry