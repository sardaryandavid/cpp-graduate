#pragma once

#include "vector.h"

namespace geometry {

struct vector_t;

/* l = p + t * d, where t is a free variable */
struct line_t {
  vector_t p_;
  vector_t d_;

  line_t() : p_(), d_() {}
  line_t(const vector_t& p, const vector_t& d) : p_(p), d_(d) {}
};
} // geometry