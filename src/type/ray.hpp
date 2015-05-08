#pragma once

#include "type/vector.hpp"

class ray {
 public:
  ray(const vector& p_origin, const vector& p_direction);

  const vector& origin() const;
  const vector& direction() const;

 private:
  vector m_origin;
  vector m_direction;
};
