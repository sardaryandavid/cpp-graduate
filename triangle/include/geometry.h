#pragma once

#include <cmath> 

/* p means plane or point 
 * t means triangle
 * l means line
 * v means vertex or vector
 * d is from the book 
 */

/* TODO: Correct */
/* Include dependencies:
 * geometry.h -> point.h -> vector.h -> line_segm.h -> line.h -> plane.h -> triangle.h 
 */

namespace geometry {
constexpr double acc = 1e-6;

inline double det(double a1, double a2, double b1, double b2) {
  return (a1 * b2 - a2 * b1);
}

inline bool is_pos(double a) {
  return (a > acc) ? true : false;
}

inline bool is_neg(double a) {
  return !is_pos(a);
}

inline bool is_eq(double a, double b) {
  return (std::fabs(b - a) < acc);
} 

inline double find_fmax(double a, double b, double c) {
  return std::fmax(std::fmax(a, b), c);
}

inline double find_fmin(double a, double b, double c) {
  return std::fmin(std::fmin(a, b), c);
}
} // geometry