#pragma once

#include <iostream>
#include <cmath>

#include "point.h"

namespace geometry {

bool solve_system(double a1, double a2, double a3, 
                  double b1, double b2, double b3,
                  double& t, double& s, bool& is_inf_sols);

struct vector_t {
  point_t v_;

  vector_t() : v_(0, 0, 0) {}
  vector_t(const point_t& v) : v_(v) {}
  vector_t(double x, double y, double z) : v_(x, y, z) {}

  point_t make_point() const;
  
  double scalar_mult(const vector_t& v) const;
  vector_t vector_mult(const vector_t& v) const;

  double len() const;
  vector_t normalize();

  vector_t operator+(const vector_t& v) const;
  vector_t operator-(const vector_t& v) const;
  vector_t operator*(double d) const;
  bool operator==(const vector_t& v) const;
  bool operator!=(const vector_t& v) const;
  
  bool inside(const point_t& min, const point_t& max) const;

  bool is_collinear(const vector_t& v) const;

  vector_t perp(const vector_t& n);

  void print() const;
};
} // geometry